#include "bst.h"

t_btree *bstree_create_node(int item) {
  t_btree *new_node = malloc(sizeof(t_btree));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->item = item;
  return new_node;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
  t_btree *cur_node = root;
  int have_inserted = 0;
  while (NULL != cur_node && !have_inserted) {
    int cmp_result = cmpf(item, cur_node->item);
    if (cmp_result > 0) {
      if (NULL != cur_node->right) {
        cur_node = cur_node->right;
      } else {
        cur_node->right = bstree_create_node(item);
        have_inserted = 1;
      }
    } else if (cmp_result < 0) {
      if (NULL != cur_node->left) {
        cur_node = cur_node->left;
      } else {
        cur_node->left = bstree_create_node(item);
        have_inserted = 1;
      }
    } else {
      have_inserted = 1;
    }
  }
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
  if (NULL != root) {
    bstree_apply_infix(root->left, applyf);
    applyf(root->item);
    bstree_apply_infix(root->right, applyf);
  }
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
  if (NULL != root) {
    applyf(root->item);
    bstree_apply_prefix(root->left, applyf);
    bstree_apply_prefix(root->right, applyf);
  }
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
  if (NULL != root) {
    bstree_apply_postfix(root->right, applyf);
    applyf(root->item);
    bstree_apply_postfix(root->left, applyf);
  }
}
