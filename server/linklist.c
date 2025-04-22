#include "linklist.h"

linknode_t *ll_create() {
  linknode_t *head = (linknode_t *)malloc(sizeof(linknode_t));
  if(!head) {
    perror("[ERROR] ll_create/malloc()");
    return NULL;
  }
  return head;
}

void ll_insert(linknode_t *head, datatype_t data) {
  linknode_t *node;

  node = (linknode_t)malloc(sizeof(linknode_t));
  if(!node) {
    perror("[ERROR] ll_insert/malloc()");
    return ;
  }
  node->data = data;
  node->next = head->next;
  head->next = node;
}

int ll_find(linknode_t *head, datatype_t data) {
  linknode_t *p;

  for(p = head->next; 
      p && memcmp(&p->data, &data, sizeof(datatype_t));
      p = p->next);

  if(p) return 1;
  else return 0;
}

void ll_delete(linknode_t *head, datatype_t data) {
  linknode_t *p, *del;

  for(p = head->next; 
      p && memcmp(&p->data, &data, sizeof(datatype_t));
      p = p->next);

  if(p) {
    del = p;
    p->next = del->next;
    free(del);
  }

  return ;
}
