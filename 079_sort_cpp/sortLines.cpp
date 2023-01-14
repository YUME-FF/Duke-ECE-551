#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char ** argv) {
  ifstream read;  //read input
  string strings;
  vector<string> ans;
  if (argc == 1) {
    while (!cin.eof()) {
      getline(cin, strings);
      ans.push_back(strings);
      sort(ans.begin(), ans.end());
      vector<string>::iterator it;
      for (it = ans.begin(); it != ans.end(); ++it) {
        cout << *it;
      }
      ans.clear();
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      read.open(argv[i]);
      if (read.fail()) {
        cerr << "Open file failed" << endl;
        return EXIT_FAILURE;
      }
      while (!read.eof()) {
        getline(read, strings);
        ans.push_back(strings);
      }
      sort(ans.begin(), ans.end());
      vector<string>::iterator it;
      for (it = ans.begin(); it != ans.end(); ++it) {
        cout << *it;
      }
      ans.clear();
      read.close();
    }
  }
  return EXIT_SUCCESS;
}
