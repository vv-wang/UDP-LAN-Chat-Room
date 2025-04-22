#ifndef __ULCRC_H__
#define __ULCRC_H__

#include "../common/protocol.h"

extern void ulcrc_send_join(int sockfd, const char *name, struct sockaddr_in to);
extern void ulcrc_send_msg(int sockfd, const char *name, struct sockaddr_in to);
extern void *ulcrc_recv_msg(void *arg);

#endif
