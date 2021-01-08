#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {}

//adds schemes facts and queries to the DatalogProgram
void DatalogProgram::addPredicate(Predicate predicate) {
  if (predicate.getType() == "Scheme") {
    schemes.push_back(predicate);
  }
  else if (predicate.getType() == "Fact") {
    facts.push_back(predicate);
  }
  else if (predicate.getType() == "Query") {
    queries.push_back(predicate);
  } 
}

void DatalogProgram::addRule(Rule rule) {
  rules.push_back(rule);
}

string DatalogProgram::toString() {
  string output = "";
  //output schemes, rules, facts, queries, and domain
  output += ("Schemes(" + to_string(schemes.size()) + "):\n");
  for (unsigned int i = 0; i < schemes.size(); i++) {
    output += ("  " + (schemes.at(i)).toString() + "\n");
  }
  output += ("Facts(" + to_string(facts.size()) + "):\n");
  for (unsigned int i = 0; i < facts.size(); i++) {
    output += ("  " + (facts.at(i)).toString()+ "\n");
  }
  output += ("Rules(" + to_string(rules.size()) + "):\n");
  for (unsigned int i = 0; i < rules.size(); i++) {
    output += ("  " + (rules.at(i)).toString() + "\n");
  }
  output += ("Queries(" + to_string(queries.size()) + "):\n");
  for (unsigned int i = 0; i < queries.size(); i++) {
    output += ("  " + (queries.at(i)).toString() + "\n");
  }
  //store parameters from Facts in domain
  vector<string> domain;
  for (unsigned int i = 0; i < facts.size(); i++) {
    vector<string> parameters = (facts.at(i)).parametersToString();
    for (unsigned int j = 0; j < parameters.size(); j++) {
      domain.push_back(parameters.at(j));
    }
  }
  //sort in alphabetical order and remove duplicates
  sort(domain.begin(), domain.end());
  domain.erase(unique(domain.begin(), domain.end()), domain.end());
  output += ("Domain(" + to_string(domain.size()) + "):\n");
  for (unsigned int i = 0; i < domain.size(); ++i) {
    output += ("  " + domain.at(i) + "\n");
  }
  return output;
}

vector<Predicate> DatalogProgram::getSchemes() {
  vector<Predicate> output;
  for (unsigned int i = 0; i < schemes.size(); i++) {
    output.push_back(schemes.at(i));
  }
  return(output);
}

vector<Predicate> DatalogProgram::getFacts() {
  vector<Predicate> output;
    for (unsigned int i = 0; i < facts.size(); i++) {
      output.push_back(facts.at(i));
    }
  return(output);
}

vector<Predicate> DatalogProgram::getQueries() {
  vector<Predicate> output;
    for (unsigned int i = 0; i < queries.size(); i++) {
      output.push_back(queries.at(i));
    }
  return(output);
}

vector<Rule> DatalogProgram::getRules() {
  vector<Rule> output;
    for (unsigned int i = 0; i < rules.size(); i++) {
      output.push_back(rules.at(i));
    }
  return(output);
}