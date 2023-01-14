#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortStrFile(FILE * f) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  char ** strFile = NULL;
  size_t count = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    strFile = realloc(strFile, (count + 1) * sizeof(*strFile));
    strFile[count++] = line;
    line = NULL;
  }
  free(line);
  sortData(strFile, count);
  for (size_t i = 0; i < count; i++) {
    printf("%s", strFile[i]);
    free(strFile[i]);
  }
  free(strFile);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      perror("Lack of file input");
      return EXIT_FAILURE;
    }
    sortStrFile(f);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  }
  else {
    for (int i = 0; i < argc - 1; i++) {
      FILE * f = fopen(argv[i + 1], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      sortStrFile(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
