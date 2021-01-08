#include "Relation.h"

Relation::Relation(string name, Header* header) {
  this->name = name;
  this->header = header;
}

string Relation::getName() {
  return name;
}

void Relation::addTuple(Tuple tuple) {
  tuples.insert(tuple);
}

Header* Relation::getHeader() {
  return header;
}

set<Tuple> Relation::getTuples() {
  return tuples;
}

int Relation::getNumTuples() {
  return tuples.size();
}

string Relation::toString() {
  string output;
  //iterate through the tuples in the set
  if (header->getValues().size() > 0) {//removes endline output when blank
    for (auto it = tuples.begin(); it != tuples.end(); it++) {
      output += "  ";
      //print each value in the tuple with corresponding header value
      for (unsigned int i = 0; i < it->getValues().size(); i++) {
        output += (header->getValues().at(i) + "=" + it->getValues().at(i));
        if (i < it->getValues().size() - 1) {
          output += ", ";
        }
      }
      output += "\n";
    }
  }
  return output;
}

Relation* Relation::select(int index, string value) {
  //returns a new relation with values in the
  //corresponding column which match given value
  Relation* relation = new Relation(name, header);
  for(auto it = tuples.begin(); it != tuples.end(); it++) {
    if (it->getValues().at(index) == value) {
      relation->addTuple(Tuple(it->getValues()));
    }
  }
  return relation;
}

Relation* Relation::select(int index1, int index2) {
  //returns a new relation with values which match
  //in the two corresponding columns
  Relation* relation = new Relation(name, header);
  for(auto it = tuples.begin(); it != tuples.end(); it++) {
    if (it->getValues().at(index1) == it->getValues().at(index2)) {
      relation->addTuple(Tuple(it->getValues()));
    }
  }
  return relation;
}

Relation* Relation::project(vector<int> indices) {
  //creates a new header with the given indices
  vector<string> columns = header->getValues();
  vector<string> newColumns;
  for (unsigned int i = 0; i < indices.size(); i++) {
    newColumns.push_back(columns.at(indices.at(i)));
  }

   //returns a new relation with the given columns
  Relation* relation = new Relation(name, new Header(newColumns));
  for(auto it = tuples.begin(); it != tuples.end(); it++) {
    vector<string> values;
    for (unsigned int i = 0; i < indices.size(); i++) {
      values.push_back(it->getValues().at(indices.at(i)));
    }
    relation->addTuple(Tuple(values));
  }
  return relation;
}

Relation* Relation::rename(vector<string> names) {
  //returns a new header with the renamed header
  Relation* relation = new Relation(name, new Header(names));
  vector<string> values;
  for(auto it = tuples.begin(); it != tuples.end(); it++) {
    relation->addTuple(Tuple(it->getValues()));
  }
  return relation;
}

void Relation::union_(Relation* otherRelation) {
  //add new tuples to relation
  set<Tuple> otherTuples = otherRelation->getTuples();
  for(auto it = otherTuples.begin(); it != otherTuples.end(); it++) {
    int tempNumTuples = getNumTuples();
    addTuple(Tuple(it->getValues()));
    //if the tuple was new, print it
    if (getNumTuples() > tempNumTuples) {
      string output = "  ";
      //print each new value in the tuple with corresponding header value
      for (unsigned int i = 0; i < it->getValues().size(); i++) {
        output += (header->getValues().at(i) + "=" + it->getValues().at(i));
        if (i < it->getValues().size() - 1) {
          output += ", ";
        }
      }
      cout << output << endl;
    }
  }
}

Relation* Relation::join(Relation* otherRelation) {
  //combine headers and create a new relation
  Header* h = combineHeaders(otherRelation->getHeader());
  Relation* result = new Relation("result", h); //check name is right

  set<Tuple> otherTuples = otherRelation->getTuples();

  //iterate through both sets of tuples and compare each pair
  for (auto it1 = tuples.begin(); it1 != tuples.end(); it1++) {
    for (auto it2 = otherTuples.begin(); it2 != otherTuples.end(); it2++) {
      vector<string> tuple1 = it1->getValues();
      vector<string> tuple2 = it2->getValues();

      //check if two tuples can join. if so, add combination to result
      if (isJoinable(tuple1, tuple2)) {
        result->addTuple(combineTuples(tuple1, tuple2));
      }
    }
  }
  return result;
}

Header* Relation::combineHeaders(Header* otherHeader) {
  vector<string> values1 = header->getValues();
  vector<string> values2 = otherHeader->getValues();

  //combine the headers
  for (unsigned int i = 0; i < values1.size(); i++) {
    for (unsigned int j = 0; j < values2.size(); j++) {
      if (values1.at(i) == values2.at(j)) {
        //adds shared column indices to a set for later
        vector<int> vals;
        vals.push_back(i);
        vals.push_back(j);
        sharedVals.insert(vals);
        break;
      }
    }
  }
  //remove duplicate values from the second header
  for(auto it = sharedVals.begin(); it != sharedVals.end(); it++) {
    values2.erase(values2.begin() + it->at(1));
  }
  for (unsigned int i = 0; i < values2.size(); i++) {
    values1.push_back(values2.at(i));
  }
  //returns combined headers
  return(new Header(values1));
}

bool Relation::isJoinable(vector<string> tuple1, vector<string> tuple2) {
  //checks if tuples match in combined columns
  unsigned int num = 0;
  for(auto it = sharedVals.begin(); it != sharedVals.end(); it++) {
    if (tuple1.at(it->at(0)) == tuple2.at(it->at(1))) {
      num += 1;
    }
  }
  if (num == sharedVals.size()) {
    return true;
  }
  else {
    return false;
  }
}

Tuple Relation::combineTuples(vector<string> tuple1, vector<string> tuple2) {
  //combines two tuples by removing shared columns values
  for(auto it = sharedVals.begin(); it != sharedVals.end(); it++) {
    tuple2.erase(tuple2.begin() + it->at(1));
  }
  for (unsigned int i = 0; i < tuple2.size(); i++) {
    tuple1.push_back(tuple2.at(i));
  }
  return tuple1;
}