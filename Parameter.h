#ifndef PARAMETER_H
#define PARAMETER_H

#include "Token.h"

class Parameter {

  public:
    Parameter(string value, bool isConstant);
    string getValue();
    bool getConstant();

  private:
    string value;
    bool isConstant;

};

#endif