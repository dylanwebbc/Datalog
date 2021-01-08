#include "Token.h"

Token::Token() {
  type = UNDEFINED;
  value = "";
  lineNum = 0;
}

//constructor
Token::Token(TokenType type, string value, int lineNum) {
  this->type = type;
  this->value = value;
  this->lineNum = lineNum;
}

string Token::toString() {
  return("(" + TokenTypeToString(type) + ",\"" + value + "\"," + to_string(lineNum) + ")");
}

//converts tokentype to a string
string Token::TokenTypeToString(TokenType type) {
  switch(type) {
    case COMMA: return "COMMA"; break;
    case PERIOD: return "PERIOD"; break;
    case Q_MARK: return "Q_MARK"; break;
    case LEFT_PAREN: return "LEFT_PAREN"; break;
    case RIGHT_PAREN: return "RIGHT_PAREN"; break;
    case COLON: return "COLON"; break;
    case COLON_DASH: return "COLON_DASH"; break;
    case MULTIPLY: return "MULTIPLY"; break;
    case ADD: return "ADD"; break;
    case SCHEMES: return "SCHEMES"; break;
    case FACTS: return "FACTS"; break;
    case RULES: return "RULES"; break;
    case QUERIES: return "QUERIES"; break;
    case ID: return "ID"; break;
    case STRING: return "STRING"; break;
    case COMMENT: return "COMMENT"; break;
    case UNDEFINED: return "UNDEFINED"; break;
    case EOFILE: return "EOF"; break;
  }
  return "ERROR";
}

TokenType Token::getType() {
  return type;
}

string Token::getValue() {
  return value;
}