#ifndef __ULCRS_H__
#define __ULCRS_H__

#include "linklist.h"

typedef struct {
  int sockfd;
  linknode_t *head;
} parm_t;

extern int ulcrs_init_socket(char *ip, char *port);
extern void *ulcrs_send_msg(void *arg);
extern void ulcrs_recv_msg(int sockfd, linknode_t *head);
extern void ulcrs_broadcast(int sockfd, linknode_t *head, msg_t msg);
extern void ulcrs_clean(parm_t *parm);

#endif
