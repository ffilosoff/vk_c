#include <printf.h>
#include "bsearch.h"

int main() {
  int a[]= {9,9,8,7,7,6,5,4,3,2,2,1,0,-1,-1,-2};
  int flag_found = 0;
  size_t index = bsearch(a, 7, 16, &flag_found);
  if (flag_found) {
    printf("%i", index);
  } else {
    printf("Not found");
  }
  return 0;
}