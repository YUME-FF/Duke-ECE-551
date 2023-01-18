#ifndef __PATHSOLUTION_H__
#define __PATHSOLUTION_H__
#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

class PathSolution {
 private:
  int dest;
  std::vector<std::vector<std::string> > ans;

 public:
  void dfs(int src,
           std::vector<std::pair<int, int> > & graph,
           std::vector<bool> & visted,
           std::vector<std::string> & temp_ans);
  std::vector<std::vector<std::string> > getAllPath(
      std::vector<std::pair<int, int> > & graph);
};
#endif
