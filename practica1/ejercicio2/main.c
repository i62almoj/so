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
#include <sys/wait.h>

#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>
#include <time.h>
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
  
    srand( time(NULL) );
      
    int i, shmid, status, indice=-1, entero, pid;
    key_t key;
    int *vector;
    void adder(int);
    struct shmid_ds buf;
    
    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, sizeof(int)*100, IPC_CREAT | 0777)) == -1)
	exit(1);

    vector = (int *) shmat(shmid, NULL, 0);
    for (int i = 0; i < 100; i++) {
      vector[i] = 0;
    }
    pid = fork();
    // Run children
    switch (pid) {
      
      case 0:{
        
        for (int i = 0; i < 10; i++) {
          while (indice<0||indice>100) {
            printf("Escribe un indice (hijo %d)\n", getpid());
            scanf("%d", &indice);
          }
          printf("Escribe un entero(hijo %d)\n", getpid());
          scanf("%d", &entero);
          vector[indice]=entero;
          indice=-1;
        }
        exit(7);
        
      }break;
      
      default:{
        pid = fork();
        // Run children
        switch (pid) {
          case 0:{
            
            for(int i = 0 ; i < 100 ; i++ ) {
              indice = rand()%100;
              vector[indice] = rand()%100;
              sleep(1);
            }
            exit(7);
            
          }break;
          default:{
            pid = fork();
            // Run children
            switch (pid) {
              case 0:{
                int cont=0;
                for (int i = 0; i < 5; i++) {
                  for (int j = 0; j < 100; j++) {
                    cont+=vector[j];
                  }
                  printf("la suma es %d\n", cont);
                  sleep(30);
                }
                exit(7);
                          
              }break;
              default:{
                            
              }break;  
            }
          }break;  
        }
        
      }break;
    }

    // Wait to finish
    for (i = 0; i < CHILDREN; i++) {
	    pid_t pid = wait(&status);
	    printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
    }

    // Final result
    
    //fprintf(stdout, "Counter: %f\n", *counter);

    // Detach segment
    shmdt(vector);

    // Mark the segment to be destroyed
    shmctl(shmid, IPC_RMID, &buf);

    return 0;
}

