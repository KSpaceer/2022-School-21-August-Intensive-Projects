#include "bst.h"
#include <stdio.h>

void bstree_apply_infix_test(void);
void bstree_apply_prefix_test(void);
void bstree_apply_postfix_test(void);
int comparator(int a, int b);
void print_item(int item);
t_btree *build_tree(int root_item, int items[], int size);
void destroy_tree(t_btree *root);

int main(void) {
  bstree_apply_infix_test();
  printf("\n\n");
  bstree_apply_prefix_test();
  printf("\n\n");
  bstree_apply_postfix_test();
  printf("\n");
  return 0;
}

int comparator(int a, int b) { return a - b; }

t_btree *build_tree(int root_item, int items[], int size) {
  t_btree *root = bstree_create_node(root_item);
  for (int i = 0; i < size; i++) {
    bstree_insert(root, items[i], comparator);
  }
  return root;
}

void destroy_tree(t_btree *root) {
  if (NULL != root) {
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
  }
}

void print_item(int item) { printf("%d ", item); }

void bstree_apply_infix_test(void) {
  printf("Infix traverse:\n");
  int items1[] = {3, 10, 1, 6, 14, 13, 4, 7};
  t_btree *root1 = build_tree(8, items1, 8);
  printf("\tFirst tree:\n\t");
  bstree_apply_infix(root1, print_item);
  destroy_tree(root1);
  int items2[] = {2, 3, 0};
  t_btree *root2 = build_tree(1, items2, 3);
  printf("\n\tSecond tree:\n\t");
  bstree_apply_infix(root2, print_item);
  destroy_tree(root2);
  int items3[] = {5, -5, 50, -555};
  t_btree *root3 = build_tree(4, items3, 4);
  printf("\n\tThird tree:\n\t");
  bstree_apply_infix(root2, print_item);
  destroy_tree(root3);
}

void bstree_apply_prefix_test(void) {
  printf("Prefix traverse:\n");
  int items1[] = {3, 10, 1, 6, 14, 13, 4, 7};
  t_btree *root1 = build_tree(8, items1, 8);
  printf("\tFirst tree:\n\t");
  bstree_apply_prefix(root1, print_item);
  destroy_tree(root1);
  int items2[] = {2, 3, 0};
  t_btree *root2 = build_tree(1, items2, 3);
  printf("\n\tSecond tree:\n\t");
  bstree_apply_prefix(root2, print_item);
  destroy_tree(root2);
  int items3[] = {5, -5, 50, -555};
  t_btree *root3 = build_tree(4, items3, 4);
  printf("\n\tThird tree:\n\t");
  bstree_apply_prefix(root2, print_item);
  destroy_tree(root3);
}

void bstree_apply_postfix_test(void) {
  printf("Postfix traverse:\n");
  int items1[] = {3, 10, 1, 6, 14, 13, 4, 7};
  t_btree *root1 = build_tree(8, items1, 8);
  printf("\tFirst tree:\n\t");
  bstree_apply_postfix(root1, print_item);
  destroy_tree(root1);
  int items2[] = {2, 3, 0};
  t_btree *root2 = build_tree(1, items2, 3);
  printf("\n\tSecond tree:\n\t");
  bstree_apply_postfix(root2, print_item);
  destroy_tree(root2);
  int items3[] = {5, -5, 50, -555};
  t_btree *root3 = build_tree(4, items3, 4);
  printf("\n\tThird tree:\n\t");
  bstree_apply_postfix(root2, print_item);
  destroy_tree(root3);
}
