#include <stdio.h>
#include <unistd.h>

int contador;
void funcao_A(void) {
  while (1) { // Loop infinito.
    printf("Para a função A contador = %d.\n", contador);
    usleep(3000000); // Dorme 3 segundos.
  }
}

void funcao_B(void) {
  while (1) { // Loop infinito.
    printf("Função B incrementando contador.\n");
    contador = contador + 1; // Incrementa contador.
    printf("Para a função B contador = %d.\n", contador);
    usleep(3000000) ; // Dorme 3 segundos.
  }
}

void main (void) {
   int pid;
   contador = 0; // Inicializa contador.
   pid = fork(); // Processo se divide em dois.
   if (pid == 0)
     funcao_A(); // Se PID igual a zero executa o código da função A.
   else
     funcao_B(); // Se PID diferente de zero executa o código da função B.
}


