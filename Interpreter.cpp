#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalogProgram) {
  this->datalogProgram = datalogProgram;

  //create relations from the schemes stored in the datalogprogram
  vector<Predicate> schemes = datalogProgram.getSchemes();
  vector<Relation*> relations;
  for (unsigned int i = 0; i < schemes.size(); i++) {
    string name = schemes.at(i).getID();
    Header* header = new Header(schemes.at(i).parametersToString());
    relations.push_back(new Relation(name, header));
  }

  //create tuples from the facts stored in the datalogprogram
  vector<Predicate> facts = datalogProgram.getFacts();
  for (unsigned int i = 0; i < facts.size(); i++) {
    string name = facts.at(i).getID();
    Tuple tuple = Tuple(facts.at(i).parametersToString());

    //add tuple to its corresponding relations
    for (unsigned int j = 0; j < relations.size(); j++) {
      if (name == relations.at(j)->getName()) {
        relations.at(j)->addTuple(tuple);
      }
    }
  }

  //create map to build database with
  map<string, Relation*> databaseMap;
  for (unsigned int i = 0; i < relations.size(); i++) {
    databaseMap[relations.at(i)->getName()] = relations.at(i);
  }

  database = new Database(databaseMap);

}

Relation* Interpreter::evaluatePredicate(const Predicate predicate) {
  Relation* relation = database->getRelation(predicate.getID());
  map<string, int> variables;
  vector<string> names;
  for (unsigned int i = 0; i < predicate.getParameters().size(); i++) {
    //check if parameter is constant (string)
    Parameter* parameter = predicate.getParameters().at(i);
    if (parameter->getConstant()) {
      //if it is constant do select type i
      relation = relation->select(i, parameter->getValue());
    }
    else {//parameter is variable (ID) -- now check if in map yet
      if (variables.find(parameter->getValue()) != variables.end()) {
        //if in the map already, do select type ii
        relation = relation->select(i, variables[parameter->getValue()]);
      }
      //otherwise, add it to map
      else {
        variables[parameter->getValue()] = i;
        names.push_back(parameter->getValue());
      }
    }
  }
  //perform a project to obtain relation with ordered columns
  //corresponding to the variables where we found them
  vector<int> columns;
  for (unsigned int i = 0; i < names.size(); i++) {
    columns.push_back(variables[names.at(i)]);
  }
  relation = relation->project(columns);

  //rename columns in relation to the variables we found
  relation = relation->rename(names);

  return relation;
}

void Interpreter::evaluateQueries() {
  cout << "Query Evaluation" << endl;
  vector<Predicate> queries = datalogProgram.getQueries();
  for (unsigned int i = 0; i < queries.size(); i++) {
    cout << queries.at(i).toString();

    Relation* relation = evaluatePredicate(queries.at(i));

    if (relation->getNumTuples() > 0) {
      cout << " Yes(" << relation->getNumTuples() << ")" << endl <<
      relation->toString();
    }
    else {
      cout << " No" << endl;
    }
  }
}

void Interpreter::evaluateRules() {
  //set up a dependency graph and the find the SCCs
  Graph graph = Graph(datalogProgram.getRules());
  cout << graph.toString();
  map<int, set<int>> SCCs = graph.DFSForest();
  cout << "Rule Evaluation" << endl;

  vector<Rule> allRules = datalogProgram.getRules();

  for (map<int, set<int>>::iterator it1 = SCCs.begin(); it1 != SCCs.end(); it1++) {

    vector<Rule> rules;
    string ruleNums;
    for (set<int>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
      rules.push_back(allRules.at(*it2));
      ruleNums += "R";
      ruleNums += to_string(*it2);
      ruleNums += ",";
    }
    ruleNums.pop_back();
    cout << "SCC: " << ruleNums << endl;

    //checks for self loops
    bool selfLoop = false;
    for (unsigned int i = 0; i < rules.size(); i++) {
      for (unsigned int j = 0; j < rules.at(i).getPredicates().size(); j++) {
        if (rules.at(i).getHead().getID() == rules.at(i).getPredicates().at(j).getID()) {
          selfLoop = true;
        }
      }
    }

    int numTuples = database->getNumTuples();
    int loops = 0;
    //FIXED POINT ALGORITHM
    //loop through each rule in the strongly connected component //until no new additions are made
    while (true) {
      loops += 1;
      for (unsigned int i = 0; i < rules.size(); i++) {
        cout << rules.at(i).toString() << endl;
        vector<Relation*> relations;

        //for reach rule, loop through predicates and evaluate them
        vector<Predicate> predicates = rules.at(i).getPredicates();
        for (unsigned int j = 0; j < predicates.size(); j++) {
          relations.push_back(evaluatePredicate(predicates.at(j)));
        }

        //natural join all the relations in this rule
        Relation* result = relations.at(0);
        if (relations.size() > 1) {
          for (unsigned int j = 1; j < relations.size(); j++) {
            result = result->join(relations.at(j));
          }
        }

        //find which columns to keep of the rules
        vector<Parameter*> ruleColumns = rules.at(i).getHead().getParameters();
        vector<string> resultColumns = result->getHeader()->getValues();
        vector<int> columnsToKeep;
        for (unsigned int j = 0; j < ruleColumns.size(); j++) {
          for (unsigned int k = 0; k < resultColumns.size(); k++) {
            if (ruleColumns.at(j)->getValue() == resultColumns.at(k)) {
              columnsToKeep.push_back(k);
              break;
            }
          }
        }
        //project the columns appearing in the head predicate
        result = result->project(columnsToKeep);

        //rename relation to make it union compatible
        vector<string> names = database->getRelation(rules.at(i).getHead().getID())->getHeader()->getValues();
        result->rename(names);

        //union relation with existing relation
        database->getRelation(rules.at(i).getHead().getID())->union_(result);
        //IMPORTANT: New tuples printed in union_ function in Relation
        
      }
      if (numTuples == database->getNumTuples()) {
        break;
      }
      else if (rules.size() == 1 && !selfLoop) {
        break;
      }
      else {
        numTuples = database->getNumTuples();
      }
    }
    cout << to_string(loops) << " passes: " << ruleNums << endl;
  }
  cout << endl;
}