#include "Automaton.h"

Automaton::Automaton(TokenType type) {
  this->type = type;
}

Token* Automaton::CreateToken(string input, int lineNumber) {
    return new Token(type, input, lineNumber); 
}

int Automaton::NewLinesRead() const {
   return newLines; 
}