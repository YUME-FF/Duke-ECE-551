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
    //writefile(page, choice, argv[1]);
    verifyPC(page, choice);
    int i = 0;
    while (page.getType(i) == 'N') {
      printfuc(page.printPage(i));
      std::vector<std::string> c = choice.printChoice(i);
      printfuc(c);
      size_t input;
      std::cin >> input;
      while (input < 1 || input > c.size()) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        std::cin >> input;
      }
      i = choice.gotopage(c[input - 1].substr(3), input, i);
    }
    printfuc(page.printPage(i));
  }
  return EXIT_SUCCESS;
}
