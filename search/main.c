#include <stdio.h>
#include "compressed_prefix_tree/compressed_prefix_tree.h"
#include "read_file/read_file.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Error: not enough arguments");
    return 2; // code: not enough arguments
  }
  struct file_handler *handler = init_file_handler(argv[1]);
  if (!is_file_opened(handler)) {
    printf("Error: file not exists or cannot be opened");
    return 3; // code: file cannot be opened
  }
  size_t max_len = 0;
  struct node *tree = tree_init();
  while (!is_eof(handler)) {
    read_string(handler);
    size_t str_len = get_last_str_length(handler);
    max_len = max_len < str_len ? str_len : max_len;
    char *str = get_last_str_pointer(handler);
    tree_add_node(tree, str, str_len - 1);
  }
  delete_file_handler(handler);
  size_t allocated_len = 1;
  char *str = malloc(sizeof(char));
  do {
    size_t str_len = 0;
    char current_char = 0;
    do {
      scanf("%c", &current_char);
      str = allocate_str(str, str_len, &allocated_len);
      if (str == 0) {
        printf("Error: not enough memory\n Exiting...");
        exit(1);
      }
      str[str_len++] = current_char;
    } while (current_char != '\n' && current_char != '\r' );
    str[str_len-1] = 0;
    if (strcmp(str, "exit")) {
      if (tree_find_node(tree, str, str_len - 1)) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  } while (strcmp(str, "exit"));
  free(str);
  return 0;
}