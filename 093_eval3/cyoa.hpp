#ifndef __CYOA_H__
#define __CYOA_H__

#include <stdlib.h>
#include <string.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "choice.cpp"
#include "page.cpp"
#include "pathsolution.cpp"

std::vector<std::string> readStoryfile(std::string filepath);

void getStory(std::vector<std::string> storyfile,
              Page & page,
              Choice & choice,
              std::string dir);

void wirtefile(Page & page, Choice & choice, std::string dir);

int checkNumFormat(std::string str);

void checkformat(std::string name);

int type1(std::string line);

int type2(std::string line);

int type3(std::string line);

int type4(std::string line);

long int strtoint(std::string num);

void verifyPC(Page & page, Choice & choice);

void dfs(int src,
         int dest,
         std::vector<std::vector<std::string> > & ans,
         std::vector<std::pair<long int, long int> > & graph,
         std::vector<bool> & visted,
         std::vector<std::string> & temp_ans);

std::vector<std::vector<std::string> > getAllPathofDest(
    std::vector<std::pair<long int, long int> > & graph,
    int dest);

void getPath(Page & page, Choice & choice);
#endif
