//
// Created by pav on 01.09.16.
//
#include "read_file.h"

struct file_handler *init_file_handler(char *file) {
  struct file_handler *handler = malloc(sizeof(struct file_handler));
  handler->file_in = fopen(file, "r");
  handler->str = malloc(sizeof(char));
  handler->str_len = 0;
  handler->str_alloc_len = 1;
  return handler;
}

// allowed null pointer
void read_string(struct file_handler *handler) {
  char current_char = 0;
  int NEOF = 0; // Not End Of File
  handler->str_len = 0;
  do {
    NEOF = fscanf(handler->file_in, "%c", &current_char);
    if (NEOF) {
      handler->str = allocate_str(handler->str, handler->str_len, &handler->str_alloc_len);
      if (!handler->str) {
        printf("Not enough memory\n exitting...\n");
        exit(1); // code: not enough memory
      }
      handler->str[handler->str_len++] = current_char;
    }
  } while (current_char != '\n' && current_char != '\r' && NEOF == 1);
  handler->str[handler->str_len - 1] = 0;
}

char *get_last_str_pointer(struct file_handler *handler) {
  return handler->str;
}

char *get_last_str_copy(struct file_handler *handler) {
  char *dist = malloc(handler->str_len * sizeof(char));
  memcpy(dist, handler->str, handler->str_len * sizeof(char));
  return dist;
}

size_t get_last_str_length(struct file_handler *handler) {
  return handler->str_len;
}

int is_eof(struct file_handler *handler) {
  return feof(handler->file_in);
}

char *allocate_str(char *str, size_t str_len, size_t *str_alloc_len) {
  if (str_len >= *str_alloc_len) {
    char *allocated_string = realloc(str, sizeof(char) * 2 * (*str_alloc_len));
    if (!allocated_string) {
      allocated_string = realloc(str, sizeof(char) * (*str_alloc_len + 1));
    } else {
      (*str_alloc_len) *= 2;
      return allocated_string;
    }
    if (!allocated_string) {
      free(str);
      return 0;
    } else {
      (*str_alloc_len)++;
      return allocated_string;
    }

  } else {
    return str;
  }
}

int is_file_opened(struct file_handler *handler) {
  return handler->file_in > 0;
}

void delete_file_handler(struct file_handler *handler) {
  free(handler->str);
  free(handler);
}