#include "Parser.h"

Parser::Parser() {}

void Parser::Match(TokenType type) {
  //throws an error if current tokentype and required type don't match
  if ((*tokens.at(numToken)).getType() == (type)) {
    numToken += 1;
    return;
  }
  throw tokens.at(numToken);
}

bool Parser::Type(TokenType type) {
  //returns true if current tokentype and required type match
  if ((*tokens.at(numToken)).getType() == (type)) {
    return true;
  }
  else {
    return false;
  }
}

DatalogProgram Parser::Parse(vector<Token*> tokens) {
  this->tokens = tokens;
  try {
    parseDatalogProgram();
    /*cout << "Success!" << endl;
    cout << datalogProgram.toString() << endl;*/
  }
  catch(Token* ERROR) { //check syntax on failure
    cout << "Failure!" << endl << "  " << ERROR->toString();
  }
  return datalogProgram;
}

void Parser::addParameter(bool isConstant) {
  if (expression) {
    string value = "";
    for (int i = 4 * numExpressions + 1; i > 0 ; i--) {
      value += tokens.at(numToken - i)->getValue(); //CHANGE THIS
    }
    parameters.push_back(new Parameter(value, isConstant));
    numExpressions = 0;
  }
  else {
    parameters.push_back(new Parameter(tokens.at(numToken - 1)->getValue(), isConstant));
  }
  
}

void Parser::storeID() {
  storedID = tokens.at(numToken - 1)->getValue();
}

void Parser::parseDatalogProgram() {
  Match(SCHEMES);
  Match(COLON);
  parseScheme();
  parseSchemeList();
  Match(FACTS);
  Match(COLON); 
  parseFactList(); 
  Match(RULES);
  Match(COLON);
  parseRuleList();
  Match(QUERIES);
  Match(COLON);
  parseQuery();
  parseQueryList();
  Match(EOFILE);
}

void Parser::parseSchemeList() {
  if (Type(ID)) {
    parseScheme();
    parseSchemeList();
  }
}

void Parser::parseFactList() {
  if (Type(ID)) {
    parseFact();
    parseFactList();
  }
}

void Parser::parseRuleList() {
  if (Type(ID)) {
    parseRule();
    parseRuleList();
  }
}

void Parser::parseQueryList() {
  if (Type(ID)) {
    parseQuery();
    parseQueryList();
  }
}

void Parser::parseScheme() {
  Match(ID);
  storeID();
  Match(LEFT_PAREN);
  Match(ID);
  addParameter(false);
  parseIDList();
  Match(RIGHT_PAREN);
  datalogProgram.addPredicate(Predicate("Scheme", storedID, parameters));
  parameters.clear();
}

void Parser::parseFact() {
  Match(ID);
  storeID();
  Match(LEFT_PAREN);
  Match(STRING);
  addParameter(true);
  parseStringList();
  Match(RIGHT_PAREN);
  Match(PERIOD);
  datalogProgram.addPredicate(Predicate("Fact", storedID, parameters));
  parameters.clear();
}

void Parser::parseRule() {
  parseHeadPredicate();
  Match(COLON_DASH);
  parsePredicate();
  parsePredicateList();
  Match(PERIOD);

  datalogProgram.addRule(Rule(predicates));
  predicates.clear();
  parameters.clear();
}

void Parser::parseQuery() {
  parsePredicate();
  Match(Q_MARK);
  datalogProgram.addPredicate(Predicate("Query", storedID, (predicates.at(0)).getParameters()));
  predicates.clear();
  parameters.clear();
}

void Parser::parseHeadPredicate() {
  Match(ID);
  storeID();
  Match(LEFT_PAREN);
  Match(ID);
  addParameter(false);
  parseIDList();
  Match(RIGHT_PAREN);
  predicates.push_back(Predicate("Head", storedID, parameters));
  parameters.clear();
}

void Parser::parsePredicate() {
  Match(ID);
  storeID();
  Match(LEFT_PAREN);
  parseParameter();
  addParameter(isConst);
  expression = false;
  parseParameterList();
  Match(RIGHT_PAREN);
  predicates.push_back(Predicate("Predicate", storedID, parameters));
  parameters.clear();
}

void Parser::parsePredicateList() {
  if (Type(COMMA)) {
    Match(COMMA);
    parsePredicate();
    parsePredicateList();
  }
}

void Parser::parseParameterList() {
  if (Type(COMMA)) {
    Match(COMMA);
    parseParameter();
    addParameter(isConst);
    expression = false;
    parseParameterList();
  }
}

void Parser::parseStringList() {
  if (Type(COMMA)) {
    Match(COMMA);
    Match(STRING);
    addParameter(true);
    parseStringList();
  }
}

void Parser::parseIDList() {
  if (Type(COMMA)) {
    Match(COMMA);
    Match(ID);
    addParameter(false);
    parseIDList();
  }
}

void Parser::parseParameter() {
  if (Type(STRING)) {
    Match(STRING);
    isConst = true;
  }
  else if (Type(ID)) {
    Match(ID);
    isConst = false;
  }
  else if (Type(LEFT_PAREN)) {
    parseExpression();
    expression = true;
    numExpressions += 1;
  }
}

void Parser::parseExpression() {
  Match(LEFT_PAREN);
  parseParameter();
  parseOperator();
  parseParameter();
  Match(RIGHT_PAREN);
}

void Parser::parseOperator() {
  if (Type(ADD)) {
    Match(ADD);
  }
  else {
    Match(MULTIPLY);
  }
}