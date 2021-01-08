#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"

class Predicate {

  public:
    Predicate(string type, string ID, vector<Parameter*> parameters);
    Predicate();
    string getType() const;
    string getID() const;
    vector<Parameter*> getParameters() const;
    vector<string> parametersToString();
    string toString();

  private:
    string type;
    string ID;
    vector<Parameter*> parameters;
};

#endif