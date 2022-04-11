#define MSGMAX 4056 // max size of message (bytes)
typedef struct mymsgbuf
{
  long msg_type; // type of message
  long sender_id; // sender identifier
  char msg[128]; // content of message
}mymsgbuf;
