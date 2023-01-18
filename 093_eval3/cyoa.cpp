#include "cyoa.hpp"

/*
Function: read txt file from path.
Input: filepath
Output: content: file content of std::vector<std::string> type
 */
std::vector<std::string> readStoryfile(std::string filepath) {
  std::ifstream read;
  std::string line;
  std::vector<std::string> content;
  filepath.append("/story.txt");
  read.open(filepath.c_str());
  if (read.fail()) {
    std::cerr << "File open failed.\n";
    exit(EXIT_FAILURE);
  }
  else {
    while (!read.eof()) {
      std::getline(read, line);
      int i = 0;
      while (line[i] == ' ') {
        ++i;
      }
      if (line[i] != 0) {
        checkformat(line);
        content.push_back(line);
      }
    }
  }
  return content;
}

/*
Function: make page and choice from story.txt
Input: storyfile
       page: Page class
       choice: Choice class
       dir: directory
*/
void getStory(std::vector<std::string> storyfile,
              Page & page,
              Choice & choice,
              std::string dir) {
  std::vector<std::string>::iterator it = storyfile.begin();
  int pageindex = 0;
  while (it != storyfile.end()) {
    std::string line = *it;
    int t1 = type1(line);
    int t2 = type2(line);
    int t3 = type3(line);
    int t4 = type4(line);
    if (t1 == 1) {  //num@type:text
      if (pageindex != strtoint(line.substr(0, line.find('@')))) {
        std::cerr << "Pagenum should be in order.\n";
        exit(EXIT_FAILURE);
      }
      std::string filename = line.substr(line.find(':') + 1, line.size());
      page.addPage(dir + "/" + filename, line[line.find('@') + 1]);
      ++pageindex;
    }
    else if (t2 == 1 || t4 == 1) {  //num:dest:choice num[var=value]:dest:choice
      int colon1Index = line.find(':');
      int colon2Index = line.find(':', colon1Index + 1);
      std::string s_pagenum = line.substr(0, colon1Index);
      if (t4 == 1) {
        int left = line.find('[');
        s_pagenum = line.substr(0, left);
      }
      long int pagenum = strtoint(s_pagenum);  //num:dest:choice

      std::string s_dest = line.substr(colon1Index + 1, colon2Index - colon1Index - 1);
      std::string text = line.substr(colon2Index + 1, line.size() - 1);
      long int dest = strtoint(s_dest);
      if (pageindex - 1 < pagenum) {
        std::cerr << "Pagenum should appear before anything else related to that page.\n";
        exit(EXIT_FAILURE);
      }
      choice.addChoice(pagenum, dest, text);
      if (t4 == 1) {  //num[var=value]:dest:choice
        int left = line.find('[');
        int equal1 = line.find('=', left + 1);
        long int val = strtoint(line.substr(equal1 + 1, line.find(']') - equal1 - 1));
        std::string var = line.substr(left + 1, equal1 - left - 1);
        choice.addVarValue(var, val, pagenum, dest);
      }
    }
    else if (t3 == 1) {  // pagenum:var = value
      int colon1 = line.find('$');
      int equal1 = line.find('=');
      std::string value = line.substr(equal1 + 1, line.size());
      page.addVarValue(line.substr(colon1 + 1, equal1 - colon1 - 1),
                       strtoint(value),
                       strtoint(line.substr(0, colon1)));
    }
    ++it;
  }
}

/*
Function: make page and choice in output format and store in output.txt
Input: page: Page class
       choice: Choice class
       dir: directory
 */
void writefile(Page & page, Choice & choice, std::string dir) {
  std::ofstream myfile;
  std::string filepath = dir + "/output.txt";
  myfile.open(filepath.c_str());
  for (int i = 0; i < page.totalNums(); i++) {
    std::vector<std::string> pageAns = page.printPage(i);  //get page file content
    std::vector<std::string>::iterator pageit = pageAns.begin();
    //print out and put every line in output.txt
    std::cout << "Page " << i << std::endl;
    std::cout << "==========" << std::endl;
    while (pageit != pageAns.end()) {
      std::cout << *pageit << std::endl;
      myfile << *pageit << std::endl;
      ++pageit;
    }
    myfile << "\n";
    if (page.getType(i) == 'N') {  //print choice and put it in output.txt
      std::vector<std::string> choiceAns = choice.printChoice(i);
      std::vector<std::string>::iterator choiceit = choiceAns.begin();
      while (choiceit != choiceAns.end()) {
        std::cout << " " << *choiceit << std::endl;
        myfile << *choiceit << std::endl;
        ++choiceit;
      }
    }
  }
  myfile.close();
}

/*
Funciton: check if string is legal number format
*/
int checkNumFormat(std::string str) {
  int num = 0;
  int i = str.size();
  if (num < i) {
    while (str[num] == ' ') {
      ++num;  //pass whitespace
    }
    while (str[num] >= 48 && str[num] <= 57) {
      ++num;  //pass normal number
    }
    if (num == i) {  //after normal number should not be whitespace:
      return 1;
    }
  }
  return 0;
}

/*
Function: check if story.txt meets the format requirement
Input: line: every line in story.txt
 */
void checkformat(std::string line) {
  int i = type1(line) + type2(line) + type3(line) + type4(line);
  if (i == 0) {
    std::cerr << "Format error.\n" << line;
    exit(EXIT_FAILURE);
  }
}

/*
Function: check input string: num@type:text
 */
int type1(std::string line) {
  //pagenum@type:string
  int i = line.find('@');
  if (i != -1) {
    int checknum = checkNumFormat(line.substr(0, i));
    if (checknum == 1) {
      //check type
      if ((line[i + 1] == 'N' || line[i + 1] == 'L' || line[i + 1] == 'W') &&
          line[i + 2] == ':') {
        return 1;
      }
    }
  }
  return 0;
}

/*
Function: check input string: pagenum:dest:text
*/
int type2(std::string line) {
  int colon1 = line.find(':');
  if (colon1 != -1) {
    int checknum1 = checkNumFormat(line.substr(0, colon1));
    if (checknum1 == 1) {  //check dest
      int colon2 = line.find(':', colon1 + 1);
      if (colon2 != -1) {
        int checknum2 = checkNumFormat(line.substr(colon1 + 1, colon2 - colon1 - 1));
        if (checknum2 == 1) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/*
Function: check input string: pagenum:var=value
*/
int type3(std::string line) {
  int colon1 = line.find('$');
  if (colon1 != -1) {
    int checknum1 = checkNumFormat(line.substr(0, colon1));
    if (checknum1 == 1) {  //check var=value
      int equal1 = line.find('=', colon1 + 1);
      if (equal1 != -1) {
        int checknum2 = checkNumFormat(line.substr(equal1 + 1, line.size()));
        if (checknum2 == 1) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/*
Function: check input string: pagenum[var=value]:dest:text
*/
int type4(std::string line) {
  int left = line.find('[');
  int colon1 = line.find(':');
  if (left != -1) {
    int checknum1 = checkNumFormat(line.substr(0, left));
    if (checknum1 == 1) {  //check [var=value]:dest:text
      int equal1 = line.find('=', left + 1);
      if (equal1 != -1) {
        int checknum2 = checkNumFormat(line.substr(equal1 + 1, colon1 - equal1 - 2));
        if (checknum2 == 1) {  //check dest
          int colon2 = line.find(':', colon1 + 1);
          if (colon2 != -1) {
            int checknum3 = checkNumFormat(line.substr(colon1 + 1, colon2 - colon1 - 1));
            if (checknum3 == 1) {
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

/*
Function: print each element in a vector
Input: ans: a template type vector
 */
template<typename T>
void printfuc(std::vector<T> ans) {
  for (size_t i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << std::endl;
  }
}

/*
Function: transform string to int
Input: num: string type number
Output: value: int type number
 */
long int strtoint(std::string num) {
  size_t index = 0;
  while (num[index] == ' ') {
    ++index;  //pass whitespace
  }
  long int value = (int)num[index++] - 48;
  while (index < num.size()) {
    value = value * 10 + (int)num[index++] - 48;
  }
  return value;
}

/*
Function: verify dest page exists;
verify everypage (except 0) is referenced by at least one other page;
verify if at least one Win and Lose page
 */
void verifyPC(Page & page, Choice & choice) {
  std::vector<std::pair<long int, long int> > c = choice.getChoice();
  std::vector<std::pair<long int, long int> >::iterator it = c.begin();
  std::vector<int> p(page.totalNums(), 0);
  //verify dest page exists
  while (it != c.end()) {
    if (it->second > page.totalNums() - 1) {
      std::cerr << "There is no such dest page exists.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (it->first != it->second) {  //except itself
      ++p[it->second];
    }
    ++it;
  }
  //verify everypage (except 0) is referenced by at least one other page
  std::vector<int>::iterator p_it = p.begin();
  while (p_it != p.end()) {
    if (p_it != p.begin() && *p_it == 0) {
      std::cerr << "pages(except 0) should be referenced by at least one other page.\n";
      exit(EXIT_FAILURE);
    }
    ++p_it;
  }
  //verify if at least one Win and Lose page
  long int win = 0;
  long int lose = 0;
  for (int i = 0; i < page.totalNums(); i++) {
    if (page.getType(i) == 'W') {
      ++win;
    }
    if (page.getType(i) == 'L') {
      ++lose;
    }
    if (win > 0 && lose > 0) {
      i = page.totalNums();
    }
  }
  if (win == 0 || lose == 0) {
    std::cerr << "There should be at least one Win and Lose page.\n";
    exit(EXIT_FAILURE);
  }
}

/*
Function: build depth first search to find path
*/
void dfs(int src,
         int dest,
         std::vector<std::vector<std::string> > & ans,
         std::vector<std::pair<long int, long int> > & graph,
         std::vector<bool> & visted,
         std::vector<std::string> & temp_ans) {
  if (src == dest) {
    ans.push_back(temp_ans);
    return;
  }
  visted[src] = true;
  long int j = 1;
  for (size_t i = 0; i < graph.size(); i++) {
    if (src == graph[i].first) {
      if (visted[graph[i].second] == false) {
        long int currPage = graph[i].first;
        std::ostringstream tmpj, tmp1;
        tmpj << j;
        tmp1 << currPage;
        std::string t = tmp1.str() + "(" + tmpj.str() + "),";
        temp_ans.push_back(t);
        dfs(graph[i].second, dest, ans, graph, visted, temp_ans);
        temp_ans.pop_back();
      }
      ++j;
    }
  }
  visted[src] = true;
}

/*
Function:get all the path to destination
*/
std::vector<std::vector<std::string> > getAllPathofDest(
    std::vector<std::pair<long int, long int> > & graph,
    int dest) {
  long int n = graph.size();
  std::vector<std::vector<std::string> > ans;
  std::vector<std::string> temp_ans;
  std::vector<bool> visted(n, false);
  dfs(graph[0].first, dest, ans, graph, visted, temp_ans);
  return ans;
}

void getPath(Page & page, Choice & choice) {
  int winnable = 0;
  for (int i = 0; i < page.totalNums(); i++) {
    if (page.getType(i) == 'W') {
      std::vector<std::pair<long int, long int> > c_tmp = choice.getChoice();
      // std::sort(c_tmp.begin(), c_tmp.end());
      std::vector<std::vector<std::string> > ans_tmp = getAllPathofDest(c_tmp, i);
      for (size_t j = 0; j < ans_tmp.size(); j++) {
        for (size_t k = 0; k < ans_tmp[j].size(); k++) {
          std::cout << ans_tmp[j][k];
        }
        std::cout << i << "(win)" << std::endl;
        winnable = 1;
      }
    }
  }
  if (winnable == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}
