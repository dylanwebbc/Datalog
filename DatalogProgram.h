#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"

#include <algorithm>

class DatalogProgram {
  public:
    DatalogProgram();
    string toString();
    void addPredicate(Predicate);
    void addRule(Rule rule);
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Predicate> getQueries();
    vector<Rule> getRules();

  private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
};

#endif