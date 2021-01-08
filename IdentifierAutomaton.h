#ifndef IDENTIFIERAUTOMATON_H
#define IDENTIFIERAUTOMATON_H

#include "Automaton.h"

class IdentifierAutomaton : public Automaton {

  public:
    IdentifierAutomaton(TokenType tokenType);
    int Read(const string& input);
    
};

#endif