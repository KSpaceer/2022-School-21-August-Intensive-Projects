#include "list.h"
#include <stdio.h>

char *add_door_test(void);
char *remove_door_test(void);
void init_testdoors(struct door *testdoors, int size);
struct node *create_testlist(struct door *testdoors, int size);
int add_door_to_beginning_test(void);
int add_door_to_end_test(void);
int add_door_to_middle_test(void);
int add_null_test(void);
int remove_door_from_beginning_test(void);
int remove_door_from_middle_test(void);
int remove_door_from_end_test(void);
int remove_null_test(void);

int main(void) {
  printf("%s\n", add_door_test());
  printf("%s\n", remove_door_test());
  return 0;
}

char *add_door_test(void) {
  int fail = add_door_to_beginning_test() || add_door_to_middle_test() ||
             add_door_to_end_test() || add_null_test();
  return fail ? "FAIL" : "SUCCESS";
}

char *remove_door_test(void) {
  int fail = remove_door_from_beginning_test() ||
             remove_door_from_middle_test() || remove_door_from_end_test() ||
             remove_null_test();
  return fail ? "FAIL" : "SUCCESS";
}

void init_testdoors(struct door *testdoors, int size) {
  for (int i = 0; i < size; i++) {
    testdoors[i].id = i;
    testdoors[i].status = 0;
  }
}

struct node *create_testlist(struct door *testdoors, int size) {
  struct node *root = NULL;
  struct node *cur_node = NULL;
  for (int i = 0; i < size; i++) {
    if (NULL == root) {
      root = add_door(NULL, &(testdoors[i]));
      cur_node = root;
    } else {
      cur_node = add_door(cur_node, &(testdoors[i]));
    }
  }
  return root;
}

int add_door_to_beginning_test(void) {
  struct door the_door = {.id = 55, .status = 1};
  struct node *root = add_door(NULL, &the_door);
  int fail = root->door != &the_door;
  destroy(root);
  return fail;
}

int add_door_to_end_test(void) {
  struct door testdoors[10];
  init_testdoors(testdoors, 10);
  struct node *root = NULL;
  struct node *last = NULL;
  struct node *cur_node = NULL;
  for (int i = 0; i < 10; i++) {
    if (NULL == root) {
      root = add_door(NULL, &(testdoors[i]));
      cur_node = root;
    } else if (9 == i) {
      last = add_door(cur_node, &(testdoors[i]));
    } else {
      cur_node = add_door(cur_node, &(testdoors[i]));
    }
  }
  struct door new_testdoor = {.id = 10, .status = 0};
  add_door(last, &new_testdoor);
  int fail = 0;
  cur_node = root;
  for (int i = 0; i < 11 && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}

int add_door_to_middle_test(void) {
  struct door testdoors[15];
  init_testdoors(testdoors, 15);
  struct node *root = NULL;
  struct node *target = NULL;
  struct node *cur_node = NULL;
  for (int i = 0; i < 15; i++) {
    if (NULL == root) {
      root = add_door(NULL, &(testdoors[i]));
      cur_node = root;
    } else {
      cur_node = add_door(cur_node, &(testdoors[i]));
      if (5 == i) {
        target = cur_node;
      }
    }
  }
  struct door new_testdoor = {.id = 55, .status = 0};
  add_door(target, &new_testdoor);
  int fail = 0;
  const int ids[] = {0, 1, 2, 3, 4, 5, 55, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  cur_node = root;
  for (int i = 0; (i < 16) && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != ids[i]) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}

int add_null_test(void) {
  struct door testdoors[5];
  init_testdoors(testdoors, 5);
  struct node *root = create_testlist(testdoors, 5);
  add_door(root, NULL);
  int fail = 0;
  struct node *cur_node = root;
  for (int i = 0; i < 5 && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}

int remove_door_from_beginning_test(void) {
  struct door testdoors[7];
  init_testdoors(testdoors, 7);
  struct node *root = create_testlist(testdoors, 7);
  root = remove_door(root, root);
  int fail = 1 == root->door->id ? 0 : 1;
  destroy(root);
  return fail;
}

int remove_door_from_middle_test(void) {
  struct door testdoors[9];
  init_testdoors(testdoors, 9);
  struct node *root = create_testlist(testdoors, 9);

  struct node *target = find_door(5, root);
  root = remove_door(target, root);
  const int ids[] = {0, 1, 2, 3, 4, 6, 7, 8};
  int fail = 0;
  struct node *cur_node = root;
  for (int i = 0; i < 8 && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != ids[i]) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}

int remove_door_from_end_test(void) {
  struct door testdoors[13];
  init_testdoors(testdoors, 13);
  struct node *root = create_testlist(testdoors, 13);
  struct node *last = find_door(12, root);
  root = remove_door(last, root);
  int fail = 0;
  struct node *cur_node = root;
  for (int i = 0; i < 12 && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}

int remove_null_test(void) {
  struct door testdoors[2];
  init_testdoors(testdoors, 2);
  struct node *root = create_testlist(testdoors, 2);
  root = remove_door(NULL, root);
  int fail = 0;
  struct node *cur_node = root;
  for (int i = 0; i < 2 && !fail; i++) {
    if (NULL == cur_node || cur_node->door->id != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
    }
  }
  fail += NULL != cur_node;
  destroy(root);
  return fail;
}
