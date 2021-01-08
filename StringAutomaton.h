#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {

  public:
    StringAutomaton(TokenType tokenType);
    int Read(const string& input);
    
};

#endif