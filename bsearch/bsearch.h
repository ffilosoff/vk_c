//
// Created by pav on 17.08.16.
//

#ifndef TEST_PROJ_BSEARCH_H
#define TEST_PROJ_BSEARCH_H

#include <stdatomic.h>

// arr - array
// x - number that search for
// n - size of array
// found - pointer that indicates if element found or not (1 or 0)
size_t bsearch(int *arr, int x, size_t n, int *found) {
  size_t begin_elem = 0, current_element = n/2, end_elem = n, last_found = n+1;
  while (end_elem - begin_elem > 1){
    if (arr[current_element] > x){
      begin_elem = current_element;
    } else{
      if (arr[current_element] == x) {
        last_found = current_element;
      }
      end_elem = current_element;
    }
    current_element = begin_elem + (end_elem-begin_elem)/2;

  }
  if (found) {
    if (last_found > n) {
      (*found) = 0;
    } else {
      (*found) = 1;
    }
  }
  return last_found;
}

#endif //TEST_PROJ_BSEARCH_H
