#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "Expected 3 or 4 arguments but got %d", argc);
    exit(EXIT_FAILURE);
  }
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Expected -n but got %s", argv[1]);
      exit(EXIT_FAILURE);
    }
  }
  FILE * fname = fopen(argv[argc - 2], "r");    //read words file
  FILE * ftemplt = fopen(argv[argc - 1], "r");  //read story template
  if (fname == NULL || ftemplt == NULL) {
    fprintf(stderr, "Unable to open the file");
    exit(EXIT_FAILURE);
  }
  catarray_t categoryList = getCatarray(fname);  //make categoryList
  //size_t record = recordN_words(&categoryList);
  size_t sz = 0;
  char * line = NULL;
  outStory_t story = initializeOutStory();  //initialize the output
  category_t * cateTrack = initialTrack();  //initialize cateTrack to record words
  while (getline(&line, &sz, ftemplt) >= 0) {
    int i = 0;
    while (line[i] != '\0') {
      if (line[i] != '_') {
        i = updateNotInterestedWords(&story, line, i);
      }
      else {  //find categoryPosition
        categoryPosition_t position = get_Position(line, i);
        i = ++position.end;
        char * cateName = getcateNamefromPosition(line, position);
        replaceCategory(cateName, &story, &categoryList, cateTrack, argc - 3);
      }
    }
    story = addLine(story);
  }
  //recoverN_words(&record, &categoryList);
  freeCategoryList(categoryList);
  free(line);
  freeCateTrack(cateTrack);
  freeAns(story);
  assert(fclose(ftemplt) == 0);
  return EXIT_SUCCESS;
}
