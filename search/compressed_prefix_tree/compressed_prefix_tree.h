//
// Created by pav on 18.08.16.
//

#ifndef SEARCH_TRIE_H
#define SEARCH_TRIE_H

#include <stdlib.h>
#include <string.h>
#include <printf.h>

struct node {
  char *key;
  size_t key_symbols;
  size_t key_symbols_allocated;
  struct node **next;
  struct node *prev;
  size_t next_count;
  size_t next_count_allocated;
  int is_root;
  int leaf;
};

struct node *tree_init();

void node_init(struct node *node1);

void tree_add_node(struct node *root, const char *str, size_t len);

int tree_find_node(struct node *root, const char *str, size_t len);

void tree_split_node(struct node *node_to_split, size_t len);

struct node *allocate_node(struct node *node1);

void not_enough_memory_error(struct node *any_node);

void delete_tree(struct node *one_node);



#endif //SEARCH_TRIE_H
