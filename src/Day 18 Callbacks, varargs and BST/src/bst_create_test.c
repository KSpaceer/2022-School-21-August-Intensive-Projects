#include "bst.h"
#include <stdio.h>

void bstree_create_node_test(void);

int main(void) {
  bstree_create_node_test();
  return 0;
}

void bstree_create_node_test(void) {
  t_btree *testnode1 = NULL;
  testnode1 = bstree_create_node(21);
  printf("%p %p %p %d\n", testnode1, testnode1->left, testnode1->right, testnode1->item);
  t_btree *testnode2 = bstree_create_node(42);
  printf("%p %p %p %d\n", testnode2, testnode2->left, testnode2->right, testnode2->item);
  t_btree *testnode3 = bstree_create_node(5);
  printf("%p %p %p %d\n", testnode3, testnode3->left, testnode3->right, testnode3->item);
  free(testnode1);
  free(testnode2);
  free(testnode3);
}

