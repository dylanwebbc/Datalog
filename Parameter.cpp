#include "Parameter.h"

Parameter::Parameter(string value, bool isConstant) {
  this->value = value;
  this->isConstant = isConstant;
}

string Parameter::getValue() {
  return value;
}

bool Parameter::getConstant() {
  return isConstant;
}