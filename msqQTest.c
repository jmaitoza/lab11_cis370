#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "mymsgbuf.h"


void create_queue(char *argv[]) {
  int msqID;
  key_t key;
  
  key = atoi(argv[2]);
  if (msgget(key, IPC_CREAT | 0666) < 0) {
    perror("[error] msgget failed!");
    exit(EXIT_FAILURE);
  }
}

int sendMsg(int argc, char *argv[]) {
  int msqID;
  key_t key;
  mymsgbuf buffer;
  size_t bufLength;

  if (argc != 5) {
    printf("[error] msgsend <flag> <key> <type> <text>\n");
    return -1;
  }

  key = atoi(argv[2]);
  msqID = msgget(key, 0666);
}

int main (int argc, char *argv[])
{
  key_t mykey;
  // if (argc != 3) {
  //   printf("[error] msqQTest -flag <key>");
  //   return -1;
  // } 

  // if create flag is set, create a new msgQueue using given key
  if (strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"-C") == 0) {
    create_queue(argv);
  }
  
  if (strcmp(argv[1],"-s") == 0 || strcmp(argv[1],"-S") == 0) {

  }

  return 0;
}
