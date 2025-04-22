#include "ulcrs.h"

int main(int argc, char *argv[]) {
  if(argc != 3) {
    fprintf(stderr, "Usage: %s <ip> <port>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  parm_t parm = {
    .sockfd = ulcrs_init_socket(argv[1], argv[2]),
    .head = ll_create()
  };

  pthread_t tid;
  pthread_create(&tid, NULL, ulcrs_send_msg, &parm);

  ulcrs_recv_msg(parm.sockfd, parm.head);
  return 0;
}
