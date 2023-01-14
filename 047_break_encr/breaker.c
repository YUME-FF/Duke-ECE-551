#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int finde(int * array) {
  int flag = 0;
  for (int i = 1; i < 26; i++) {
    if (array[i] > array[flag]) {
      flag = i;
    }
  }
  return flag;
}

void frecount(FILE * f, int * array) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 97]++;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int array[26] = {0};
  frecount(f, array);
  int e = finde(array);
  int key = e >= 4 ? (e - 4) : (e - 4 + 26);
  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
