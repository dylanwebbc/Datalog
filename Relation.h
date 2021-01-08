#ifndef RELATION_H
#define RELATION_H

#include "Header.h"
#include "Tuple.h"

#include <set>

class Relation {
  public:
    Relation(string name, Header* header);
    void addTuple(Tuple tuple);
    string toString();
    string getName();
    Header* getHeader();
    set<Tuple> getTuples();
    int getNumTuples();

    Relation* select(int index, string value);
    Relation* select(int index1, int index2);
    Relation* project(vector<int> indices);
    Relation* rename(vector<string> names);
    void union_(Relation* otherRelation);
    Relation* join(Relation* relation);

    Header* combineHeaders(Header* otherHeader);
    bool isJoinable(vector<string> tuple1, vector<string> tuple2);
    Tuple combineTuples(vector<string> tuple1, vector<string> tuple2);

  private:
    string name;
    Header* header;
    set<Tuple> tuples;
    set<vector<int>> sharedVals;

};

#endif