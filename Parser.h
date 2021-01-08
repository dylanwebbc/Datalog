#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "DatalogProgram.h"

class Parser : protected Token {

  public:
    Parser();
    DatalogProgram Parse(vector<Token*> tokens);

  private:
    DatalogProgram datalogProgram;
    vector<Token*> tokens;
    vector<Parameter*> parameters;
    vector<Predicate> predicates;
    string storedID;
    int numToken = 0;
    void Match(TokenType type);
    bool Type(TokenType type);
    void addParameter(bool isConstant);
    bool isConst;
    void storeID();
    bool expression;
    int numExpressions;

    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIDList();
    void parseParameter();
    void parseExpression();
    void parseOperator();

};

#endif