#include "ulcrs.h"

int ulcrs_init_socket(char *ip, char *port) {
  int sockfd;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) {
    perror("[ERROR] ulcrs_init_socket/socket()");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr = {
    .sin_family = AF_INET,
    .sin_addr.s_addr = inet_addr(ip),
    .sin_port = htons(atoi(port))
  };

  if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("ulcrs_init_socket/bind()");
    exit(EXIT_FAILURE);
  }

  return sockfd;
}

void *ulcrs_send_msg(void *arg) {
  parm_t parm;
  msg_t msg;

  parm = *(parm_t *)arg;
  strcpy(msg.name, "server");
  while(1) {
    printf("server> ");
    memset(msg.buf, 0, sizeof(msg.buf));
    fgets(msg.buf, sizeof(msg.buf), stdin);
    msg.buf[strcspn(msg.buf, "\n")] = '\0';
    msg.type = (strncmp(msg.buf, MSG_QUIT, sizeof(MSG_QUIT)) == 0) ? SERVER_QUIT : SERVER_CHAT;

    ulcrs_broadcast(parm.sockfd, parm.head, msg);
    if(msg.type == SERVER_QUIT) {
      ulcrs_clean(&parm);
      break;
    }
  }
  exit(EXIT_SUCCESS);
}

void ulcrs_recv_msg(int sockfd, linknode_t *head) {
  msg_t msg;
  struct sockaddr_in from;
  socklen_t len;

  len = sizeof(from);
  while(1) {
    memset(&msg, 0, sizeof(msg));
    if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&from, &len) < 0) {
      perror("ulcrs_recv_msg/recvfrom()");
      exit(EXIT_FAILURE);
    }

    switch(msg.type) {
      case CLIENT_JOIN:
        if(!ll_find(head, from)) {
          ll_insert(head, from);
        }
        break;
      case CLIENT_QUIT:
        ll_remove(head, from);
        break;
      case CLIENT_CHAT:
        break;
    }
    ulcrs_broadcast(sockfd, head, msg);
  }
}

void ulcrs_broadcast(int sockfd, linknode_t *head, msg_t msg) {
  linknode_t *p;

  p = head->next;
  while(p) {
    if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&p->data, sizeof(datatype_t)) < 0) {
      perror("ulcrs_broadcast/sendto()");
      exit(EXIT_FAILURE);
    }
    p = p->next;
  }
}

void ulcrs_clean(parm_t *parm) {
  linknode_t *p, *del;

  close(parm->sockfd);
  p = parm->head->next;
  free(parm->head);
  while(p) {
    del = p;
    p = p->next;
    free(del);
  }
}
