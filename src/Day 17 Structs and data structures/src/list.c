#include "list.h"

struct node *init(struct door *door) {
  struct node *root = malloc(sizeof(struct node));
  if (root) {
    root->door = door;
    root->next = NULL;
  }
  return root;
}

struct node *add_door(struct node *elem, struct door *door) {
  struct node *new_door = door != NULL ? init(door) : NULL;
  if (NULL != elem && NULL != new_door) {
    struct node *next_door = elem->next;
    elem->next = new_door;
    new_door->next = next_door;
  }
  return new_door;
}

struct node *find_door(int door_id, struct node *root) {
  struct node *cur_door = root;
  while (NULL != cur_door && cur_door->door->id != door_id) {
    cur_door = cur_door->next;
  }
  return cur_door;
}

struct node *remove_door(struct node *elem, struct node *root) {
  struct node *cur_node = root;
  struct node *prev_node = NULL;
  while (cur_node != NULL && cur_node != elem) {
    prev_node = cur_node;
    cur_node = cur_node->next;
  }
  if (NULL != cur_node) {
    if (NULL != prev_node) {
      prev_node->next = elem->next;
    } else {
      root = elem->next;
    }
    elem->next = NULL;
    destroy(cur_node);
  }
  return root;
}

void destroy(struct node *root) {
  struct node *cur_node = root;
  struct node *next_node = NULL;
  while (NULL != cur_node) {
    next_node = cur_node->next;
    free(cur_node);
    cur_node = next_node;
  }
}
