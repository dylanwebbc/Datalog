#include "Header.h"

Header::Header(vector<string> values) {
  this->values = values;
}

vector<string> Header::getValues() {
  return values;
}