#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

#define TAMANHO_PILHA 65536

// Variável compartilhada
int contador = 0;

static int funcao_A(void *arg) {
    while (1) { // Loop infinito.
        printf("Para a função A contador = %d.\n", contador);
        usleep(3000000); // Dorme 3 segundos.
    }
    return 0;
}

static int funcao_B(void *arg) {
    while (1) { // Loop infinito.
        printf("Função B incrementando contador.\n");
        contador = contador + 1; // Incrementa contador.
        printf("Para a função B contador = %d.\n", contador);
        usleep(3000000); // Dorme 3 segundos.
    }
    return 0;
}

int main(void) {
    void *pilha_A, *pilha_B;
    int pid_A, pid_B;

    // Aloca pilha para a thread A.
    pilha_A = malloc(TAMANHO_PILHA);
    if (pilha_A == NULL) {
        perror("Erro na alocação da pilha para função A.");
        exit(1);
    }

    // Aloca pilha para a thread B.
    pilha_B = malloc(TAMANHO_PILHA);
    if (pilha_B == NULL) {
        perror("Erro na alocação da pilha para função B.");
        exit(1);
    }

    contador = 0; // Inicializa contador.

    // A pilha no x86 cresce de cima para baixo, por isso somamos o TAMANHO_PILHA
    pid_A = clone(funcao_A, (char *)pilha_A + TAMANHO_PILHA, CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|SIGCHLD, NULL);
    if (pid_A == -1) {
        perror("Erro ao criar thread A");
        exit(1);
    }

    pid_B = clone(funcao_B, (char *)pilha_B + TAMANHO_PILHA, CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|SIGCHLD, NULL);
    if (pid_B == -1) {
        perror("Erro ao criar thread B");
        exit(1);
    }

    // Aguarda o término dos processos criados
    waitpid(pid_A, NULL, 0);
    waitpid(pid_B, NULL, 0);

    // Libera a memória alocada
    free(pilha_A);
    free(pilha_B);

    return 0;
}
