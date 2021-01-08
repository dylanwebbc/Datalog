#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
  public:
    Interpreter(DatalogProgram datalogProgram);
    Relation* evaluatePredicate(const Predicate predicate);
    void evaluateQueries();
    void evaluateRules();

  private:
    DatalogProgram datalogProgram;
    Database* database;

};

#endif