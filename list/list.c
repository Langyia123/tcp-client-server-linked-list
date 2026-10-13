// list/list.c
// 
// Implementation for linked list.
//
// Langyia Philemon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  malloc(sizeof(list_t)); 
  if (mylist == NULL){
    return NULL;
  }
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  if (l == NULL){
    return;
  }
  node_t *curr = l->head;
  while (curr != NULL){
    node_t *next = curr->next;
    free(curr);
    curr = next;
  }
  l->head = NULL;
  free(l);
}

void list_print(list_t *l) {
  if (l == NULL){
    return;
  }
  node_t *curr = l->head;
  while (curr != NULL){
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) {
  if (l == NULL){
    char* buf = malloc(5);
    if (buf == NULL){
      return NULL;
    }
    strcpy(buf, "NULL");
    return buf;
  }
  size_t size = 5;
  node_t *curr = l->head;
  while (curr != NULL) {
    int chars = snprintf(NULL, 0, "%d->", curr->value);
    size += chars;
    curr = curr->next;
  }
  char *buf = malloc(size);
  if (buf == NULL){
    return NULL;
  }
  char *position = buf;
  size_t remaining = size;
  curr = l->head;
  while (curr != NULL){
    int written = snprintf(position, remaining, "%d->", curr->value);
    position += written;
    remaining -= written;
    curr = curr->next;
  }
  snprintf(position, remaining, "NULL");
  return buf;
}

int list_length(list_t *l) {
  if (l == NULL){
    return 0;
  }
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL){
    count ++;
    curr = curr->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  if (l == NULL){
    return;
  }
  node_t *new_node = getNode(value);
  if (new_node == NULL){
    return;
  }
  if (l->head == NULL){
    l->head = new_node;
    return;
  }
  node_t *curr = l->head;
  while (curr->next != NULL){
    curr = curr->next;
  }
  curr->next = new_node;
}
void list_add_to_front(list_t *l, elem value) {
  if (l == NULL){
    return;
  }
  node_t *new_node = getNode(value);

  /* Insert to front */
  //node_t *head = l->head;  // get head of list
  if (new_node == NULL){
    return;
  }
  new_node->next = l->head;
  l->head = new_node;
}

node_t * getNode(elem value) {
  node_t *mynode = malloc(sizeof(node_t));
  if (mynode == NULL){
    return NULL;
  }
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (l == NULL || index < 1){
    return;
  }
  if (index == 1){
    list_add_to_front(l, value);
    return;
  }
  node_t *curr = l->head;
  int position = 1;
  while (curr != NULL && position < index-1){
    curr = curr->next;
    position ++;
  }
  if (curr == NULL){
    return;
  }
  node_t * new_node = getNode(value);
  if (new_node == NULL){
    return;
  }
  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) { 
  if (l== NULL || l->head == NULL){
    return -1;
  }
  if (l ->head->next == NULL){
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }
  node_t *curr = l->head;
  while (curr->next ->next != NULL){
    curr = curr->next;
  }
  node_t *last = curr->next;
  elem value = last->value;
  curr->next = NULL;
  free(last);
  return value; 
}
elem list_remove_from_front(list_t *l) { 
  if (l == NULL || l->head == NULL){
    return -1;
  }
  node_t *temp = l->head;
  elem value = temp->value;
  l->head = temp->next;
  free(temp);
  return value; 
}
elem list_remove_at_index(list_t *l, int index) {
  if (l == NULL ||l->head == NULL || index < 1){
    return -1;
  }
  if (index == 1){
    return list_remove_from_front(l);
  }
  node_t *curr = l->head;
  int position = 1;
  while (curr != NULL && position < index-1){
    curr = curr->next;
    position ++;
  }
  if (curr == NULL || curr->next == NULL){
    return -1;
  }
  node_t * removed = curr->next;
  elem value = removed->value;
  curr->next = removed->next;
  free(removed);
  return value;
}

bool list_is_in(list_t *l, elem value) { 
  if (l == NULL){
    return false;
  }
  node_t *curr = l->head;
  while (curr != NULL){
    if (curr->value == value){
      return true;
    }
    curr = curr->next;
  }
  return false; 
}
elem list_get_elem_at(list_t *l, int index) { 
  if (l == NULL || index < 1){
    return -1;
  }
  node_t *curr = l->head;
  int position = 1;
  while (curr != NULL){
    if (position == index){
      return curr->value;
    }
    curr = curr->next;
    position ++;
  }
  return -1; 
}
int list_get_index_of(list_t *l, elem value) { 
  if (l == NULL){
    return -1;
  }
  node_t *curr = l->head;
  int index = 1;
  while (curr != NULL){
    if (curr->value == value){
      return index;
    }
    curr = curr->next;
    index ++;
  }
  return -1; 
}

 