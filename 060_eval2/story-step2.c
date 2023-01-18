#include "rand_story.h"
int main(int argc, char ** argv) {
  FILE * f = initialFile(argc, argv);
  catarray_t categoryList = getCatarray(f);  //make categoryList
  printWords(&categoryList);
  freeCategoryList(categoryList);
  return EXIT_SUCCESS;
}
