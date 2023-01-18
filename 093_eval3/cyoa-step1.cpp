#include "cyoa.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Unexpected number of arguments.\n";
    return EXIT_FAILURE;
  }
  else {
    Page page;
    Choice choice;
    std::vector<std::string> storyfile = readStoryfile(argv[1]);
    getStory(storyfile, page, choice, argv[1]);
    writefile(page, choice, argv[1]);
  }
  return EXIT_SUCCESS;
}
