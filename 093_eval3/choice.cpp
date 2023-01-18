#include "choice.hpp"

//default constructor
Choice::Choice() :
    pageDestPair(std::vector<std::pair<long int, long int> >()),
    text(std::vector<std::string>()),
    varvalue(std::vector<std::pair<std::string, long int> >()) {
}

//copy constructor
Choice::Choice(const Choice & rhs) :
    pageDestPair(rhs.pageDestPair), text(rhs.text), varvalue(rhs.varvalue) {
}

//assignment operator
Choice & Choice::operator=(const Choice & rhs) {
  if (this != &rhs) {
    std::vector<std::pair<long int, long int> > temp = rhs.pageDestPair;
    std::vector<std::string> textTmp = rhs.text;
    pageDestPair = temp;
    text = textTmp;
    std::vector<std::pair<std::string, long int> > temp2 = rhs.varvalue;
    varvalue = temp2;
  }
  return *this;
}

Choice::~Choice() {
}

//get Choice
std::vector<std::pair<long int, long int> > Choice::getChoice() {
  return pageDestPair;
}

//getText
std::string Choice::getText(const long int pagenum, const long int dest) const {
  std::vector<std::pair<long int, long int> >::const_iterator it = pageDestPair.begin();
  long int index = 0;
  while (it != pageDestPair.end()) {
    if (*it == std::make_pair(pagenum, dest)) {
      return text[index];
    }
    else {
      ++it;
      ++index;
    }
  }
  std::cerr << "There is no such choice.\n";
  exit(EXIT_FAILURE);
}

std::pair<std::string, long int> Choice::getvarvalue(const long int pagenum,
                                                     const long int dest) {
  std::vector<std::pair<long int, long int> >::const_iterator it = pageDestPair.begin();
  long int index = 0;
  while (it != pageDestPair.end()) {
    if (*it == std::make_pair(pagenum, dest)) {
      return varvalue[index];
    }
    else {
      ++it;
      ++index;
    }
  }
  std::cerr << "There is no such choice.\n";
  exit(EXIT_FAILURE);
}

void Choice::addChoice(const long int pagenum, const long int dest, const std::string t) {
  pageDestPair.push_back(std::make_pair(pagenum, dest));
  varvalue.push_back(std::make_pair("", 0));
  text.push_back(t);
}

void Choice::addVarValue(const std::string var,
                         const long int val,
                         const long int pagenum,
                         const long int dest) {
  std::vector<std::pair<long int, long int> >::const_iterator it = pageDestPair.begin();
  long int index = 0;
  while (it != pageDestPair.end()) {
    if (*it == std::make_pair(pagenum, dest)) {
      varvalue[index] = std::make_pair(var, val);
      it = pageDestPair.end();
    }
    else {
      ++it;
      ++index;
    }
  }
}

//print choice of pagenum
std::vector<std::string> Choice::printChoice(
    const long int pagenum,
    std::vector<std::pair<std::string, long int> > vvinput) {
  assert(pagenum >= 0);
  std::vector<std::string> ans;
  std::vector<std::pair<long int, long int> >::const_iterator it = pageDestPair.begin();
  long int index = 0;
  int i = 1;
  while (it != pageDestPair.end()) {
    if (it->first == pagenum) {
      int ind = i;
      std::string str;
      std::ostringstream temp;
      temp << ind;
      str = temp.str();
      int unavailable = 0;
      int exist = 0;
      std::vector<std::pair<std::string, long int> >::iterator vvit = vvinput.begin();
      while (vvit != vvinput.end()) {
        if ((*vvit).first == varvalue[index].first) {
          exist = 1;
          if ((*vvit).second != varvalue[index].second) {
            unavailable = 1;
            ans.push_back(str + ". <UNAVAILABLE>");
            break;
          }
        }
        ++vvit;
      }
      if (unavailable == 0) {
        if (exist == 0 && varvalue[index].first != "" && varvalue[index].second != 0) {
          ans.push_back(str + ". <UNAVAILABLE>");
        }
        else {
          ans.push_back(str + ". " + text[index]);
        }
      }
      i++;
    }
    ++it;
    ++index;
  }
  return ans;
}

void Choice::printChoicelist() {
  if (pageDestPair.size() == 0) {
    std::cout << "There is no choice.";
  }
  else {
    std::vector<std::pair<long int, long int> >::iterator it = pageDestPair.begin();
    long int index = 0;
    while (it != pageDestPair.end()) {
      std::cout << "Page number is: " << it->first << ". Destination is :" << it->second
                << std::endl;
      std::cout << "text is : " << text[index] << std::endl;
      std::cout << "varValue pair: var is: " << varvalue[index].first
                << " and value is :" << varvalue[index].second << std::endl;
      ++it;
      ++index;
    }
  }
}

long int Choice::gotopage(const std::string mychoice,
                          const size_t choice,
                          const long int pagenum) {
  int j = choice;
  for (size_t i = 0; i < text.size(); i++) {
    if (pagenum == pageDestPair[i].first) {
      --j;
      if (j == 0 && text[i] == mychoice) {
        return pageDestPair[i].second;
      }
    }
  }
  return 0;
}
