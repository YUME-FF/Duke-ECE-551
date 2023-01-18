#include "page.hpp"

//default constructor
Page::Page() :
    pageName(std::vector<std::pair<std::string, char> >()),
    pageNum(0),
    varValue(std::vector<std::pair<int, std::pair<std::string, long int> > >()) {
}

Page::Page(long int n) :
    pageName(std::vector<std::pair<std::string, char> >(n)),
    pageNum(n),
    varValue(std::vector<std::pair<int, std::pair<std::string, long int> > >(n)) {
}

//copy constructor
Page::Page(const Page & rhs) :
    pageName(rhs.pageName), pageNum(rhs.pageNum), varValue(rhs.varValue) {
}

//assignment operator
Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    std::vector<std::pair<std::string, char> > temp = rhs.pageName;
    pageNum = rhs.pageNum;
    pageName = temp;
    std::vector<std::pair<int, std::pair<std::string, long int> > > temp2 = rhs.varValue;
    varValue = temp2;
  }
  return *this;
}

Page::~Page() {
}

//get pagenum
int Page::totalNums() const {
  return pageNum;
}

//get type
char Page::getType(const long int index) {
  assert(index >= 0 && index < pageNum);
  std::vector<std::pair<std::string, char> >::iterator it = pageName.begin();
  long int i = index;
  while (it != pageName.end()) {
    if (i > 0) {
      --i;
      ++it;
    }
    else {
      return it->second;
    }
  }
  return it->second;
}

//add page
void Page::addPage(const std::string name, const char type) {
  pageName.push_back(std::make_pair(name, type));
  pageNum++;
}

void Page::addVarValue(const std::string var,
                       const long int val,
                       const long int whichpage) {
  varValue.push_back(std::make_pair(whichpage, std::make_pair(var, val)));
}

std::vector<std::pair<std::string, long int> > Page::getVarValue(
    const long int whichpage) {
  std::vector<std::pair<std::string, long int> > ans;
  std::vector<std::pair<int, std::pair<std::string, long int> > >::iterator it =
      varValue.begin();
  while (it != varValue.end()) {
    if ((*it).first == whichpage) {
      ans.push_back((*it).second);
    }
    ++it;
  }
  return ans;
}

//print the index th page
std::vector<std::string> Page::printPage(const long int index) {
  assert(index >= 0 && index < pageNum);
  std::vector<std::string> ans;
  long int i = 0;
  std::vector<std::pair<std::string, char> >::iterator it = pageName.begin();
  while (i < index) {
    ++i;
    ++it;
  }
  std::ifstream read;
  std::string line;
  read.open(it->first.c_str());
  if (read.fail()) {
    std::cerr << "File open failed.\n";
    exit(EXIT_FAILURE);
  }
  else {
    while (!read.eof()) {
      std::getline(read, line);
      ans.push_back(line);
    }
  }
  //From type to 3 kinds of print
  if (it->second == 'N') {
    ans.push_back("What would you like to do?\n");
  }
  else if (it->second == 'L') {
    ans.push_back("Sorry, you have lost. Better luck next time!");
  }
  else if (it->second == 'W') {
    ans.push_back("Congratulations! You have won. Hooray!");
  }
  return ans;
}

//print whole page
void Page::printPagelist() {
  if (pageNum == 0) {
    std::cout << "There is no page.";
  }
  else {
    std::vector<std::pair<std::string, char> >::iterator it = pageName.begin();
    while (it != pageName.end()) {
      std::cout << "Type is: " << it->second << std::endl;
      std::cout << "Page path is: " << it->first << std::endl;
      ++it;
    }
  }
}
