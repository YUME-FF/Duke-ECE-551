#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readmat(FILE * f, char mat[10][10]) {
  char c;
  int i = 0, j = 0;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (j != 10) {
        fprintf(stderr, "column size of matrix is wrong\n");
        exit(EXIT_FAILURE);
      }
      else {
        j = 0;
        i++;
        continue;
      }
    }
    mat[i][j] = c;
    j++;
  }

  if (i != 10) {
    fprintf(stderr, "row size of matrix is wrong\n");
    exit(EXIT_FAILURE);
  }
}

void swap(char * a, char * b) {
  char temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void rotate(char mat[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < i; j++) {
      swap(&mat[i][j], &mat[j][i]);
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 5; j++) {
      swap(&mat[i][j], &mat[i][9 - j]);
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", mat[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage:file_name longInt1 longint2");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  char mat[10][10];
  readmat(f, mat);
  rotate(mat);
}
