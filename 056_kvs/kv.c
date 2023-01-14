#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    exit(EXIT_FAILURE);
  }
  kvarray_t * pairs = malloc(sizeof(*pairs));
  pairs->kvPairs = NULL;
  pairs->length = 0;
  char * line = NULL;
  size_t sz = 0;
  size_t num = 0;
  while (getline(&line, &sz, f) >= 0) {
    pairs->length++;
    pairs->kvPairs = realloc(pairs->kvPairs, pairs->length * sizeof(*pairs->kvPairs));

    kvpair_t * pair = malloc(sizeof(*pair));
    pair->key = line;
    char * pointerKey = strchr(pair->key, '=');
    if (pointerKey != NULL) {
      *pointerKey = '\0';
    }
    pointerKey++;
    pair->value = pointerKey;
    char * pointerValue = strchr(pair->value, '\n');
    if (pointerValue != NULL) {
      *pointerValue = '\0';
    }

    pairs->kvPairs[num] = pair;
    num++;

    line = NULL;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file");
    exit(EXIT_FAILURE);
  }
  free(line);
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->kvPairs[i]->key);
    free(pairs->kvPairs[i]);
  }
  free(pairs->kvPairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i]->key, pairs->kvPairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->kvPairs[i]->key, key) == 0) {
      return pairs->kvPairs[i]->value;
    }
  }
  return NULL;
}
