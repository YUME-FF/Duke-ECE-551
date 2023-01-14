#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE M
  counts_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->arrSize = 0;
  ans->unknown = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    int ifexist = 0;
    //update time
    for (int i = 0; i < c->arrSize; i++) {
      if (!strcmp(name, c->arr[i]->string)) {
        c->arr[i]->strCount++;
        ifexist = 1;
      }
    }
    if (ifexist == 0) {
      c->arrSize++;
      c->arr = realloc(c->arr, c->arrSize * sizeof(*c->arr));
      one_count_t * tmpname = malloc(sizeof(*tmpname));
      c->arr[c->arrSize - 1] = tmpname;
      c->arr[c->arrSize - 1]->string = name;
      c->arr[c->arrSize - 1]->strCount = 1;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->arrSize; i++) {
    fprintf(outFile, "%s:%d\n", c->arr[i]->string, c->arr[i]->strCount);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown>:%d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->arrSize; i++) {
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}
