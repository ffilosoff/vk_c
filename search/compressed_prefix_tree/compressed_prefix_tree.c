//
// Created by pav on 01.09.16.
//

#include "compressed_prefix_tree.h"

struct node *tree_init() {
  struct node *root = malloc(sizeof(struct node));
  root->key = 0;
  root->key_symbols = 0;
  root->key_symbols_allocated = 0;
  root->next = 0;
  root->prev = 0;
  root->next_count = 0;
  root->next_count_allocated = 0;
  root->leaf = 0;
  root->is_root = 1;
  return root;
}

void node_init(struct node *node1) {
  node1->key = 0;
  node1->key_symbols = 0;
  node1->key_symbols_allocated = 0;
  node1->next = 0;
  node1->prev = 0;
  node1->next_count = 0;
  node1->next_count_allocated = 0;
  node1->leaf = 0;
  node1->is_root = 0;
}

void tree_add_node(struct node *root, const char *str, size_t len) {
  int found_node = 0;
  for (size_t i = 0; i < root->next_count; i++) {
    size_t split_symbol = 0;
    for (size_t j = 0; j < root->next[i]->key_symbols && j < len; j++) {
      if (root->next[i]->key[j] == str[j]) {
        split_symbol++;
        found_node = 1;
      } else {
        break;
      }
    }
    if (found_node) {
      if (split_symbol == root->next[i]->key_symbols) {
        tree_add_node(root->next[i], str + split_symbol, len - split_symbol);
      }
      if (split_symbol < root->next[i]->key_symbols) {
        tree_split_node(root->next[i], split_symbol);
        if (split_symbol == len) {
          root->next[i]->leaf = 1;
          return;
        }
        tree_add_node(root->next[i], str + split_symbol, len - split_symbol);
      }
      break;
    }
  }
  if (!found_node) {
    struct node *new_node = allocate_node(root);
    new_node->key = malloc(len * sizeof(char));
    if (new_node->key == 0) {
      not_enough_memory_error(root);
    }
    new_node->key_symbols = new_node->key_symbols_allocated = len;
    memcpy(new_node->key, str, new_node->key_symbols * sizeof(char));
    new_node->leaf = 1;
//    }
  }
}

int tree_find_node(struct node *root, const char *str, size_t len) {
  int symbol_count = 0;
  int found = 0;
  for (int i = 0; i < root->next_count; i++) {
    for (int j = 0; j < root->next[i]->key_symbols && root->next[i]->key_symbols <= len; j++) {
      if (root->next[i]->key[j] == str[j]) {
        symbol_count++;
        found = 1;
      } else {
        found = 0;
        break;
      }
    }
    if (symbol_count && found) {
      if (symbol_count == len) {
        if (root->next[i]->leaf) {
          return 1;
        } else {
          return 0;
        }
      }
      if (symbol_count == root->next[i]->key_symbols) {
        return tree_find_node(root->next[i], str + symbol_count * sizeof(char), len - symbol_count);
      }
      break;
    }
  }
  return 0;
}

void tree_split_node(struct node *node_to_split, size_t len) {
  struct node *node_between = malloc(sizeof(struct node));
  if (!node_between) {
    not_enough_memory_error(node_to_split);
  }
  node_init(node_between);

  node_between->prev = node_to_split;
  node_between->leaf = node_to_split->leaf;
  node_between->next = node_to_split->next;
  node_between->next_count = node_to_split->next_count;
  node_between->next_count_allocated = node_to_split->next_count_allocated;
  node_between->key_symbols = node_between->key_symbols_allocated = node_to_split->key_symbols - len;
  node_between->key = malloc(node_between->key_symbols * sizeof(char));
  if (!node_between->key) {
    not_enough_memory_error(node_to_split);
  }
  memcpy(node_between->key, len * sizeof(char) + node_to_split->key, node_between->key_symbols);
  node_to_split->key_symbols = len;
  node_to_split->next = malloc(sizeof(struct node *));
  if (!node_to_split->next) {
    delete_tree(node_between);
    not_enough_memory_error(node_to_split);
  }
  node_to_split->next_count = node_to_split->next_count_allocated = 1;
  node_to_split->next[0] = node_between;
  node_to_split->leaf = 0;
  node_to_split->key[node_to_split->key_symbols] = 0;
}

struct node *allocate_node(struct node *node1) {
  node1->next = realloc(node1->next, (node1->next_count + 1) * sizeof(struct node *));
  if (node1->next == 0) {
    not_enough_memory_error(node1);
  }
  struct node *new_node = node1->next[node1->next_count] = malloc(sizeof(struct node));
  if (new_node == 0) {
    not_enough_memory_error(node1);
  }
  node_init(new_node);
  new_node->prev = node1;
  node1->next_count++;
  return new_node;
}

// trying to free memory before exit if error of not enough memory
void not_enough_memory_error(struct node *any_node) {
  while (!any_node->is_root) {
    any_node = any_node->prev;
  }
  delete_tree(any_node);
  printf("Not enough memory\n exitting...\n");
  exit(1); //not enough memory code exit
}

void delete_tree(struct node *one_node) {
  if (one_node->next_count != 0) {
    for (int i = 0; i < one_node->next_count; i++) {
      delete_tree(one_node->next[i]);
    }
  }
  if (!one_node->key) {
    free(one_node->key);
  }
  if (!one_node->is_root) {
    free(one_node);
  }
}