#include "ulcrc.h"

int main(int argc, char *argv[]) {
  if(argc != 4) {
    fprintf(stderr, "[ERROR] Usage: %s <ip> <port> <name>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) {
    perror("[ERROR] main/socket()");
    exit(EXIT_FAILURE);
  } 

  struct sockaddr_in server_addr = {
    .sin_family = AF_INET,
    .sin_addr.s_addr = inet_addr(argv[1]),
    .sin_port = htons(atoi(argv[2]))
  };

  ulcrc_send_join(sockfd, argv[3], server_addr);

  pthread_t tid;
  pthread_create(&tid, NULL, ulcrc_recv_msg, (void *)&sockfd);

  ulcrc_send_msg(sockfd, argv[3], server_addr);

  return 0;
}
