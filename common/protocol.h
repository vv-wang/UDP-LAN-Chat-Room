#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define CLIENT_JOIN 10
#define CLIENT_QUIT 20
#define CLIENT_CHAT 30
#define SERVER_CHAT 40
#define SERVER_QUIT 50

#define MSG_QUIT    "quit"

#define SZ_NAME     15
#define SZ_BUF      1024

typedef struct {
    char type;
    char name[SZ_NAME];
    char buf[SZ_BUF];
} msg_t;

#endif
