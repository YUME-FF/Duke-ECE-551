#include "rand_story.h"
int main(int argc, char ** argv) {
  FILE * f = initialFile(argc, argv);
  size_t sz = 0;
  char * line = NULL;
  outStory_t story = initializeOutStory();  //initialize the output
  while (getline(&line, &sz, f) >= 0) {
    int i = 0;
    while (line[i] != '\0') {
      if (line[i] != '_') {
        i = updateNotInterestedWords(&story, line, i);
      }
      else {  //find categoryPosition
        categoryPosition_t position = get_Position(line, i);
        char * category = getcateNamefromPosition(line, position);
        i = ++position.end;
        replaceCategory(category, &story, NULL, NULL, 0);
      }
    }
    story = addLine(story);
  }
  free(line);
  freeAns(story);
  assert(fclose(f) == 0);
  return EXIT_SUCCESS;
}
