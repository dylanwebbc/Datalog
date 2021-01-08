#include "Database.h"

Database::Database(map<string, Relation*> relations) {
  this->relations = relations;
}

Relation* Database::getRelation(string name) {
  return relations[name];
}

int Database::getNumTuples() {
  int total = 0;
  for (map<string, Relation*>::iterator it = relations.begin(); it != relations.end(); it++){
    total += it->second->getNumTuples();
  }
  return total;
}