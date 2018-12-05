#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
  key_t key;
  int shmid;
  char * data;

  key = ftok("mykey", 'f');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, 0);

  if (data[0])
  {
    printf("Here are my contents: %s\n", data);
  }
  else
  {
    printf("I'm created\n");
  }

  char input[200];
  printf("Add segment? enter 'y'\n");
  
  fgets(input, 200, stdin);

  if(!strcmp(input, "y\n")){
    printf("Enter a new string! \n" );
    fgets(input, 200, stdin);
    input[strlen(input)-1] = 0;
    strcpy(data, input);
  }
  printf("Delete segment? enter 'y'\n");
  fgets(input, 200, stdin);

  if(!strcmp(input, "y\n")){
    shmdt(data);
    
    shmctl(shmid, IPC_RMID, NULL);
    printf("Deleted\n");
  }

  return 0;

}