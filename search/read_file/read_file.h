//
// Created by pav on 01.09.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SEARCH_READ_FILE_H
#define SEARCH_READ_FILE_H

struct file_handler {
  FILE *file_in;
  char *str;
  size_t str_len;
  size_t str_alloc_len;
};

struct file_handler *init_file_handler(char *file);

void read_string(struct file_handler *handler);

// method does NOT copying the data, just giving the pointer that will be alive till reading next string or
// deleting file_handler object
char *get_last_str_pointer(struct file_handler *handler);

// this method will copy string to new space with memcpy, this method more secure than get_last_str_pointer
char *get_last_str_copy(struct file_handler *handler);

size_t get_last_str_length(struct file_handler *handler);

char *allocate_str(char *str, size_t str_len, size_t *str_alloc_len);

void delete_file_handler(struct file_handler *handler);

int is_eof(struct file_handler *handler);

int is_file_opened(struct file_handler *handler);


#endif //SEARCH_READ_FILE_H
