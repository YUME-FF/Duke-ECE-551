#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t ans = 0;
  size_t temp = 1;
  if (n > 0) {
    for (size_t i = 0; i < n - 1; i++) {
      if (array[i] < array[i + 1]) {
        temp++;
      }
      else {
        if (ans < temp) {
          ans = temp;
        }
        temp = 1;
      }
    }
    if (ans < temp) {
      ans = temp;
    }
  }
  return ans;
}
