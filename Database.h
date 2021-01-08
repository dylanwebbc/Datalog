#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"

#include <map>

class Database {
  public:
    Database(map<string, Relation*> relations);
    Relation* getRelation(string name);
    int getNumTuples();

  private:
    map<string, Relation*> relations;

};

#endif