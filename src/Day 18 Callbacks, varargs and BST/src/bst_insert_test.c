#include "bst.h"
#include <stdio.h>

void bstree_insert_test(void);
void tree_building_test(int root_item, int items[], int size);
int comparator(int a, int b);
t_btree *find_elem(t_btree *root, t_btree **parent, int *side, int item,
                   int (*cmpf)(int, int));
void destroy_tree(t_btree *root);

int main(void) {
  bstree_insert_test();
  return 0;
}

int comparator(int a, int b) { return a - b; }

void bstree_insert_test(void) {
  int items1[] = {3, 10, 1, 6, 14, 13, 4, 7};
  tree_building_test(8, items1, 8);
  printf("\n");
  int items2[] = {2, 3, 0};
  tree_building_test(1, items2, 3);
  printf("\n");
  int items3[] = {5, -5, 50, -555};
  tree_building_test(4, items3, 4);
}

void tree_building_test(int root_item, int items[], int size) {
  t_btree *root = bstree_create_node(root_item);
  for (int i = 0; i < size; i++) {
    bstree_insert(root, items[i], comparator);
    t_btree *parent = NULL;
    int side = 0;
    t_btree *cur_node = find_elem(root, &parent, &side, items[i], comparator);
    if (NULL != parent && NULL != cur_node) {
      printf("Inserted new tree node with item = %d as %s child of tree node "
           "with item = %d.\n",
           cur_node->item, side ? "right" : "left", parent->item);
    }
  }
  destroy_tree(root);
}

t_btree *find_elem(t_btree *root, t_btree **parent, int *side, int item,
                   int (*cmpf)(int, int)) {
  t_btree *cur_node = root;
  t_btree *prev_node = NULL;
  while (NULL != cur_node && cur_node->item != item) {
    int cmp_result = cmpf(item, cur_node->item);
    if (cmp_result < 0) {
      prev_node = cur_node;
      *side = 0;
      cur_node = cur_node->left;
    } else {
      prev_node = cur_node;
      *side = 1;
      cur_node = cur_node->right;
    }
  }
  *parent = prev_node;
  return cur_node;
}

void destroy_tree(t_btree *root) {
  if (NULL != root) {
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
  }
}
