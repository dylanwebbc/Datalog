#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Parameter.h"

class Expression : public Parameter {
  public:
    Expression(vector<Parameter> parameters);

  private:
    vector<Parameter> parameters;

};

#endif