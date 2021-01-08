#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum TokenType {
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, 
  COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, 
  QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFILE
};

class Token {

  public:
    Token();
    Token(TokenType type, string value, int lineNum);

    string toString();
    TokenType getType();
    string getValue();
  
  protected:
    string TokenTypeToString(TokenType type);

    TokenType type;
    string value;
    int lineNum;

};

#endif