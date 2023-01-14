#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void check_fail(int * array, size_t n, size_t ans) {
  if (maxSeq(array, n) == ans) {
    printf("test case passed\n");
  }
  else {
    printf("test case failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array_0[3] = {0};
  int array_1[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int array_2[6] = {-2, 0, 1, 2, 1, 5};
  int array_3[6] = {5, 4, 3, 2, 1, 0};
  int array_4[1] = {1};
  check_fail(array_4, 1, 1);
  int array_5[5] = {-1, -2, -3, 0, 1};
  check_fail(array_5, 5, 3);
  int array_6[4] = {1, 1, 2, 1};
  check_fail(array_6, 4, 2);
  int array_7[3] = {1, 1, 1};
  check_fail(array_7, 3, 1);
  int array_8[5] = {-2, -1, 0, -3, -4};
  check_fail(array_8, 5, 3);
  int array_9[7] = {1, 2, 1, 2, 3, 1, 2};
  check_fail(array_9, 7, 3);
  int array10[3] = {1, 2, 3};
  check_fail(array_0, 3, 1);
  check_fail(array_1, 10, 4);
  check_fail(array_2, 6, 4);
  check_fail(array_3, 6, 1);
  check_fail(array10, 3, 3);
  int array11[0];
  check_fail(array11, 0, 0);

  return EXIT_SUCCESS;
}
