#ifndef UNDEFINEDAUTOMATON_H
#define UNDEFINEDAUTOMATON_H

#include "Automaton.h"

class UndefinedAutomaton : public Automaton {

  public:
    UndefinedAutomaton(TokenType tokenType);
    int Read(const string& input);
    
};

#endif