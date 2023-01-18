#ifndef __PAGE_H__
#define __PAGE_H__

#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
class Page {
 private:
  std::vector<std::pair<std::string, char> > pageName;  //<filename, type>
  long int pageNum;
  std::vector<std::pair<int, std::pair<std::string, long int> > > varValue;
  //<pagenum, <variable, value>>

 public:
  Page();
  Page(long int n);
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  int totalNums() const;
  char getType(const long int index);
  ~Page();
  void addPage(const std::string name, const char type);
  void addVarValue(const std::string var, const long int val, const long int whichpage);
  std::vector<std::pair<std::string, long int> > getVarValue(const long int whichpage);
  std::vector<std::string> printPage(const long int index);
  void printPagelist();
};
#endif
