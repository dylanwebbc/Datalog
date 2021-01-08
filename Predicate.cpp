#include "Predicate.h"
  
Predicate::Predicate(string type, string ID, vector<Parameter*> parameters) {
  this->parameters = parameters;
  this->type = type;
  this->ID = ID;
}

string Predicate::getType() const {
  return type;
}

string Predicate::getID() const {
  return ID;
}

vector<Parameter*> Predicate::getParameters() const {
  return parameters;
}

vector<string> Predicate::parametersToString() {
  vector<string> output;
  for (unsigned int i = 0; i < parameters.size(); i++) {
    output.push_back(parameters.at(i)->getValue());
  }
  return output;
}

string Predicate::toString() {
  string output = "";
  output += ID;
  output += "(";
  for (unsigned int i = 0; i < parameters.size(); ++i) {
    output += (parameters.at(i))->getValue();
    if (i < parameters.size() - 1) {
      output += ",";
    }
  }
  output += ")";
  if (type == "Fact") {
    output += ".";
  }
  else if (type == "Query") {
    output += "?";
  }
  return output;
}