#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <semaphore.h>

#define TAMANHO_PILHA 65536

sem_t mutex;

void up(sem_t *sem) {
  sem_wait(sem);
}

void down(sem_t *sem) {
  sem_post(sem);
}

typedef struct { // Simula registro de saldo em conta.
  char nome[50]; // Nome do correntista.
  double saldo; // Saldo da conta.
} Registro;
Registro registro[500];

//Função para criação de conta.
void cria_conta(char *nome, int numero, float saldo) {
  strcpy(registro[numero].nome, nome);
  registro[numero].saldo = saldo;
}

// Função para mostrar a conta.
void mostra_conta(int numero) {
  printf("A conta de %s possui R$%.2f.\n", registro[numero].nome, registro[numero].saldo);
}

// Função para a leitura do registro da conta.
Registro le_registro(int conta) {
  return registro[conta];
}

// Função para gravação do registro da conta
void grava_registro(Registro reg, int conta){
  registro[conta] = reg;
}

// Função para atualização do saldo da conta.
void atualiza_saldo(double valor, int conta) {
  Registro reg;
  printf("Operação [%.2f] vai entrar na região critica\n", valor);
  up(&mutex); // Inicio da região crítica.
  printf("Operação [%.2f] entrou na região critica\n", valor);
  reg = le_registro(conta); // le o registro da conta
  printf("Iniciando operação [%.2f] (saldo atual = R$%.2f)\n", valor, reg.saldo);
  usleep(1000); // Pequena pausa.
  reg.saldo = reg.saldo + valor; // Atualiza saldo
  grava_registro(reg, conta); // Grava saldo atualizado na conta.
  printf("Terminada a operação [%.2f] (saldo atual = R$%.2f)\n", valor, reg.saldo);
  printf("Operação [%.2f] saindo da região crítica\n", valor);
  down(&mutex);
}

int funcaoDeposito(void *arg) {
  atualiza_saldo(100, 231); //Faz deposito de 100,00
  return 0;
}

int funcaoSaque(void *arg) {
  atualiza_saldo(-200, 231); //Faz saque de 200,00
  return 0;
}

int main() {
  void *pilha1, *pilha2;
  int pid1, pid2;
  
  sem_init(&mutex, 1, 1);
  
  // Cria conta para teste.
  cria_conta("Ricardo Valerio", 231, 500);
  printf("Saldo antes das operações: ");
  mostra_conta(231);
  
  // Aloca pilha para thread de depósito
  if ((pilha1 = malloc(TAMANHO_PILHA)) == 0) {
  perror("Erro na alocação da pilha.");
  exit(1);
  }
  
  // Aloca pilha para thread de saque
  if ((pilha2 = malloc(TAMANHO_PILHA)) == 0) {
  perror("Erro na alocação da pilha.");
  exit(1);
  }
  // Inicia thread de deposito
  pid1 = clone(funcaoDeposito, pilha1 + TAMANHO_PILHA, CLONE_VM | SIGCHLD, NULL);
  // Inicia thread de SAQUE
  pid2 = clone(funcaoSaque, pilha2 + TAMANHO_PILHA, CLONE_VM | SIGCHLD, NULL);
  
  //Aguarda final das operações
  waitpid(pid1, 0, 0);
  waitpid(pid2, 0, 0);
  
  printf("Saldo depois das operações: ");
  mostra_conta(231);
  
  return 0;
}

