#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Header {
  public:
    Header(vector<string> values);
    vector<string> getValues();

  private:
    vector<string> values;

};

#endif