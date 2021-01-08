#ifndef RULE_H
#define RULE_H

#include "Predicate.h"

class Rule {
  public:
    Rule(vector<Predicate> predicates);
    string toString();
    vector<Predicate> getPredicates();
    Predicate getHead();

  private:
    vector<Predicate> predicates;
};

#endif