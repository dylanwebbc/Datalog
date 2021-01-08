#include "Graph.h"

Graph::Graph(vector<Rule> rules) {
  //iterates through each node and stores dependent nodes as edges
  for (unsigned int i = 0; i < rules.size(); i++) {
    set<int> dependentNodes;
    vector<Predicate> predicates = rules.at(i).getPredicates();
    for (unsigned int j = 0; j < predicates.size(); j++) {
      for (unsigned int k = 0; k < rules.size(); k++) {
        if (rules.at(k).getHead().getID() == predicates.at(j).getID()) {
          dependentNodes.insert(k);
        }
      }
    }
    dependencies[i] = dependentNodes;
    visited[i] = false;
  }

  //reverses dependency graph
  for (unsigned int i = 0; i < rules.size(); i++) {
    set<int> rDependentNodes;
    for (map<int, set<int>>::iterator it = dependencies.begin(); it != dependencies.end(); it++) {
      set<int>::iterator itFind = it->second.find(i);
      if (itFind != it->second.end()) {
        rDependentNodes.insert(it->first);
      }
    }
    reverseDependencies[i] = rDependentNodes;
  }
}

string Graph::toString() {
  string output = "Dependency Graph\n";
  //iterates through each node and prints its adjacent nodes
  for (map<int, set<int>>::iterator it1 = dependencies.begin(); it1 != dependencies.end(); it1++) {
    output += "R";
    output += to_string(it1->first);
    output += ":";
    for (set<int>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
      output += "R";
      output += to_string(*it2);
      output += ",";
    }
    if (it1->second.size() > 0) {
      output.pop_back();
    }
    output += "\n";
  }
  return output;
}

//finds postorder of a single tree
void Graph::postOrderTree(int vertex) {
  visited[vertex] = true;
  set<int> adjacencies = reverseDependencies[vertex];
  for (set<int>::iterator it = adjacencies.begin(); it != adjacencies.end(); it++) {
    if (!visited[*it]) {
      postOrderTree(*it);
    }
  }
  postorder.push_back(vertex);
}

//finds the postorder of the entire reverse dependency graph
void Graph::postOrderForest() {
  for (map<int, set<int>>::iterator it = reverseDependencies.begin(); it != reverseDependencies.end(); it++) {
    if (!visited[it->first]) {
      postOrderTree(it->first);
    }
  }
}

//performs a DFS on a single tree
void Graph::DFSTree(int vertex) {
  visited[vertex] = true;
  set<int> adjacencies = dependencies[vertex];
  for (set<int>::iterator it = adjacencies.begin(); it != adjacencies.end(); it++) {
    if (!visited[*it]) {
      DFSTree(*it);
    }
  }
  SCC.insert(vertex);
}

//performs a DFS on the dependency graph and returns SCCs
map<int, set<int>> Graph::DFSForest() {
  postOrderForest();
  reverse(postorder.begin(),postorder.end());
  map<int, set<int>> forest;
  for (map<int, set<int>>::iterator it = dependencies.begin(); it != dependencies.end(); it++) {
    visited[it->first] = false;
  }
  int numTree = 0;
  for (unsigned int i = 0; i < postorder.size(); i++) {
    if (!visited[postorder.at(i)]) {
      DFSTree(postorder.at(i));
      forest[numTree] = SCC;
      SCC.clear();
      numTree += 1;
    }
  }
  cout << endl;
  return forest;
}