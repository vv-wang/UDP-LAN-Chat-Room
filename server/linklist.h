#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "../common/protocol.h"

typedef struct sockaddr_in datatype_t;

typedef struct node {
  datatype_t data;
  struct node *next;
} linknode_t;

linknode_t *ll_create();
void ll_insert(linknode_t *head, datatype_t data);
int ll_find(linknode_t *head, datatype_t data);
void ll_delete(linknode_t *head, datatype_t data);

#endif
