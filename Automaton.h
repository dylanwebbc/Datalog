#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Token.h"

class Automaton {

  public:
    Automaton(TokenType type);
    virtual int Read(const string& input) = 0;
    virtual Token* CreateToken(string input, int lineNumber);
    virtual int NewLinesRead() const;

  protected:
    int newLines = 0;
    TokenType type;
    
};

#endif