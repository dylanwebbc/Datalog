#include "Rule.h"
  
Rule::Rule(vector<Predicate> predicates) {
  this->predicates = predicates;
}

string Rule::toString() {
  string output = "";
  output += (predicates.at(0)).toString(); //head predicate
  output += " :- ";
  for (unsigned int i = 1; i < predicates.size(); ++i) {
    output += predicates.at(i).toString();
    if (i < predicates.size() - 1) {
      output += ",";
    }
  }
  output += ".";
  return output;
}

vector<Predicate> Rule::getPredicates() {
  vector<Predicate> output;
  for (unsigned int i = 1; i < predicates.size(); i++) {
    output.push_back(predicates.at(i));
  }
  return output;
}

Predicate Rule::getHead() {
  return predicates[0];
}