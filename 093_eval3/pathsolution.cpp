#include "pathsolution.hpp"

void PathSolution::dfs(int src,
                       std::vector<std::pair<int, int> > & graph,
                       std::vector<bool> & visted,
                       std::vector<std::string> & temp_ans) {
  if (src == dest) {
    ans.push_back(temp_ans);
    return;
  }
  visted[src] = true;

  for (size_t i = 0; i < graph.size(); i++) {
    if (src == graph[i].first && visted[graph[i].first] == false) {
      int currPage = graph[i].first;
      int nextPage = graph[i].second;
      std::ostringstream tmp1, tmp2;
      tmp1 << currPage;
      tmp2 << nextPage;
      std::string t = tmp1.str() + "(" + tmp2.str() + ")";
      temp_ans.push_back(t);
      dfs(graph[i].first, graph, visted, temp_ans);
      temp_ans.pop_back();
    }
  }
  visted[src] = true;
}
std::vector<std::vector<std::string> > PathSolution::getAllPath(
    std::vector<std::pair<int, int> > & graph) {
  int n = graph.size();
  std::vector<std::string> temp_ans;
  std::vector<bool> visted(n, false);
  int currPage = graph[0].first;
  int nextPage = graph[0].second;
  std::ostringstream tmp1, tmp2;
  tmp1 << currPage;
  tmp2 << nextPage;
  std::string t = tmp1.str() + "(" + tmp2.str() + ")";
  temp_ans.push_back(t);
  dfs(graph[0].first, graph, visted, temp_ans);
  return ans;
}
