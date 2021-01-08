#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Tuple {
  public:
    Tuple(vector<string> values);
    vector<string> getValues() const;
    bool operator< (const Tuple & other) const;

  private:
    vector<string> values;

};

#endif