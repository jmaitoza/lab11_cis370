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
  msqID = msgget(key, 0666); //access msg queue

  buffer.msg_type = atoi(argv[3]); //msg buffer type
  strncpy(buffer.msg, argv[4], 128); // copies the first 128 characters from argv[4] to buffer.msg
  bufLength = strlen(buffer.msg) + 1;
  msgsnd(msqID, &buffer, bufLength, IPC_NOWAIT);
  
  printf("Msg received (%ld): %s\n",buffer.msg_type ,buffer.msg);
  return -1;
}

int receiveMsg(int argc, char *argv[]) {
  int msqID;
  key_t key;
  mymsgbuf buffer;

  if (argc != 4) {
    printf("[error] msqQTest -r/R <key> <type>\n");
    return -1;
  }

  key = atoi(argv[2]);
  msqID = msgget(key, 0666);

  msgrcv(msqID, &buffer, 128, atoi(argv[3]), 0);
  printf("(%ld): %s\n", buffer.msg_type, buffer.msg);
  return -1;
}

int removeQueue(int argc, char *argv[]) {
  int msqID;
  key_t key;
  if (argc != 3) {
    printf("[error] msqQTest -d/D <key>");
    return -1;
  }
  key = atoi(argv[2]);
  msqID = msgget(key,0666);

  if (msgctl(msqID, IPC_RMID, 0) == -1) {
    return (-1);
  }
  return(0);
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
  
  // if send flag is set, send a message using given key
  if (strcmp(argv[1],"-s") == 0 || strcmp(argv[1],"-S") == 0) {
    sendMsg(argc, argv);
  }

  // if receive flag is set, receive message using given key
  if (strcmp(argv[1],"-r") == 0 || strcmp(argv[1],"-R") == 0) {
    receiveMsg(argc, argv);     
  }

  // if the delete flag is set, delete message queue
  if (strcmp(argv[1],"-d") == 0 || strcmp(argv[1],"-D") == 0) {
    removeQueue(argc, argv);
  }

  return 0;
}
