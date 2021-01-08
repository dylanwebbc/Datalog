#include "Tuple.h"

Tuple::Tuple(vector<string> values) {
  this->values = values;
}

vector<string> Tuple::getValues() const {
  return values;
}

bool Tuple::operator< (const Tuple & other) const {
      if (values < other.getValues()) {
        return true;
      }
      else {
        return false;
      }
    }