#include <stdio.h>
#include <unistd.h>

void main ( int argc, char **argv, char* envp[]) {  
  printf("Iniciando execução do código do processo filho.\n");
  printf("Processo filho em execução (PID: %d). PID do pai = %d\n", getpid(), getppid());
  while (1) { // Loop infinito.
    usleep(1000000); // Dorme 1 segundo.
  }
}
