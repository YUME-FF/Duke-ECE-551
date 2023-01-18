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
    std::vector<std::pair<std::string, long int> > varvalue;
    while (page.getType(i) == 'N') {
      std::vector<std::pair<std::string, long int> > pagevarvalue = page.getVarValue(i);
      std::vector<std::pair<std::string, long int> >::iterator it = pagevarvalue.begin();
      while (it != pagevarvalue.end()) {
        if ((*it).first != "" || (*it).second != 0) {
          int j = 0;
          std::vector<std::pair<std::string, long int> >::iterator vvit =
              varvalue.begin();
          while (vvit != varvalue.end()) {
            if ((*vvit).first == (*it).first) {
              (*vvit).second = (*it).second;
              j = 1;
              break;
            }
            ++vvit;
          }
          if (j == 0) {
            varvalue.push_back(*it);
          }
        }
        ++it;
      }
      printfuc(page.printPage(i));
      std::vector<std::string> c = choice.printChoice(i, varvalue);
      //according to varvalue, print choice
      printfuc(c);
      size_t input;
      std::cin >> input;
      while (input < 1 || input > c.size() ||
             c[input - 1].substr(3, c[input - 1].size()) == "<UNAVAILABLE>") {
        if (input >= 1 && input <= c.size()) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
        }
        else {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
        std::cin >> input;
      }
      i = choice.gotopage(c[input - 1].substr(3), input, i);
    }
    printfuc(page.printPage(i));
  }
  return EXIT_SUCCESS;
}
