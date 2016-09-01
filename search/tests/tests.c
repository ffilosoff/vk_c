//
// Created by pav on 01.09.16.
//

#include "tests.h"

void ok(int expr){
  static unsigned int ok_count = 0;
  if(expr){
    printf("ok %u\n", ok_count);
  } else {
    printf("NOT ok %u\n", ok_count);
  }
  ok_count++;
}

void test_tree() {
  struct node *root = tree_init();
  tree_add_node(root, "asdf", 4);//1
  tree_add_node(root, "asdt", 4);//2
  tree_add_node(root, "asdm", 4);
  tree_add_node(root, "qwer", 4);//3
  tree_add_node(root, "hgjfkdsla", 9);
  tree_add_node(root, "ud", 2);//4
  ok(tree_find_node(root,"asdf", 4) == 1);
  ok(tree_find_node(root,"asdt", 4) == 1);
  ok(tree_find_node(root,"asdm", 4) == 1);
  ok(tree_find_node(root,"qwer", 4) == 1);
  ok(tree_find_node(root,"hgjfkdsla", 9) == 1);
  ok(tree_find_node(root,"ud", 2) == 1);

  ok(tree_find_node(root,"qw", 2) == 0);
  ok(tree_find_node(root,"", 0) == 0);
  ok(tree_find_node(root,"asd",3)==0);

//  printf("%d %d %d %d", tree_find_node(root, "asdft", 3), tree_find_node(root, "asdt", 4),
//         tree_find_node(root, "qwer", 4), tree_find_node(root, "ud", 2));
  delete_tree(root);
}

void test_file_handler() {
  struct file_handler *handler = init_file_handler("tst.in");
  while (!is_eof(handler)) {
    read_string(handler);
    char *str = get_last_str_pointer(handler);
    printf("%s\n", str);
  }
  delete_file_handler(handler);
}