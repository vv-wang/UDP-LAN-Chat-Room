#include "ulcrc.h"

void ulcrc_send_join(int sockfd, const char *name, struct sockaddr_in to) {
  msg_t msg;

  msg.type = CLIENT_JOIN;
  strcpy(msg.name, name);
  strcpy(msg.buf, "Join the room.");

  if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&to, sizeof(to)) < 0) {
    perror("ulcrc_send_join/sendto()");
    exit(EXIT_FAILURE);
  }
}

void ulcrc_send_msg(int sockfd, const char *name, struct sockaddr_in to) {
  msg_t msg;
  
  strcpy(msg.name, name);

  while(1) {
    printf("%s>", msg.name);
    memset(&msg, 0, sizeof(msg));
    fgets(msg.buf, sizeof(msg.buf), stdin);
    msg.buf[strcspn(msg.buf, "\n")] = '\0';
    msg.type = (strncmp(msg.buf, MSG_QUIT, sizeof(MSG_QUIT)) == 0) ? CLIENT_QUIT : CLIENT_CHAT;

    if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&to, sizeof(to)) < 0) {
      perror("ulcrc/send_chat/sendto()");
      exit(EXIT_FAILURE);
    }
    
    if (msg.type == CLIENT_QUIT){
      printf("[INFO] %s offline.\n", msg.name);
      close(sockfd);
      exit(EXIT_SUCCESS);
    }
  }
}

void *ulcrc_recv_msg(void *arg) {
  int sockfd;
  msg_t msg;
  struct sockaddr_in from;
  socklen_t len;

  sockfd = *(int *)arg;
  len = sizeof(from);

  while(1) {
    memset(&msg, 0, sizeof(msg));

    if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&from, &len) < 0) {
      perror("[ERROR] ulcrc_recv_chat/recvfrom()");
      exit(EXIT_FAILURE);
    }
    printf("[INFO] %s: %s\n", msg.name, msg.buf);

    if (msg.type == SERVER_QUIT) {
      exit(EXIT_SUCCESS);
    }
  }
}



