#ifndef GRAPH_H
#define GRAPH_H

#include "Rule.h"
#include <set>
#include <map>
#include <algorithm>

class Graph {
  public:
    Graph(vector<Rule> rules);
    map<int, set<int>> DFSForest();
    string toString();

  private:
    map<int, set<int>> dependencies;
    map<int, set<int>> reverseDependencies;
    map<int, bool> visited;
    vector<int> postorder;
    set<int> SCC;

    void postOrderTree(int vertex);
    void postOrderForest();
    void DFSTree(int vertex);

};

#endif