/** ­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
@file main.c
@brief This file includes the code to create 3 child processes for the same parent
and wait untill all child processes had finished to finish the parent process
@author Javier Cebrián Muñoz
@date 24/09/2018
@version 1.0
­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>

#define CHILDREN	3

// The process finished correctly
#define Ok	7

/** ­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
@fn main(int argc, char const *argv[])
@brief Creatse 3 child processes for the same parent
and wait untill all child processes had finished to finish the parent process
@pre  none
@return 0
@author Javier Cebrián Muñoz
@date 24/09/2018
­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­*/
int main(){
  int i, status;

// Run children
  if (!fork()) {
    exit(Ok);
  }
  if (!fork()) {
    exit(Ok);
  }
  if (!fork()) {
    exit(Ok);
  }
// Wait to finish
  for (i = 0; i < CHILDREN; i++) {
    pid_t pid = wait(&status);
    printf("Child %d finished with status %d\n", pid, WEXITSTATUS(status));
  }

// Final result
  fprintf(stdout, "Program finished\n");

  return 0;
}
