#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (expected_ans == ans) {
    printf("Great. The result is expected_ans");
  }
  else {
    printf("Sorry. The result does not correct.");
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(5, 1, 5);
  run_check(-2, 2, 4);
  run_check(-2, 3, -8);
  run_check(0, 0, 1);
  return EXIT_SUCCESS;
}
