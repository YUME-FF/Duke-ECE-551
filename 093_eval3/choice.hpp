#ifndef __CHOICE_H__
#define __CHOICE_H__

#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
class Choice {
 private:
  std::vector<std::pair<long int, long int> > pageDestPair;
  std::vector<std::string> text;
  std::vector<std::pair<std::string, long int> > varvalue;

 public:
  Choice();
  Choice(const Choice & rhs);
  Choice & operator=(const Choice & rhs);
  std::string getText(const long int pagenum, const long int dest) const;
  std::vector<std::pair<long int, long int> > getChoice();
  std::pair<std::string, long int> getvarvalue(const long int pagenum,
                                               const long int dest);
  ~Choice();
  void addChoice(const long int pagenum, const long int dest, const std::string t);
  void addVarValue(const std::string var,
                   const long int val,
                   const long int pagenum,
                   const long int dest);
  std::vector<std::string> printChoice(
      const long int pagenum,
      std::vector<std::pair<std::string, long int> > vvinput =
          std::vector<std::pair<std::string, long int> >());
  void printChoicelist();
  long int gotopage(const std::string mychoice,
                    const size_t choice,
                    const long int pagenum);
};

#endif
