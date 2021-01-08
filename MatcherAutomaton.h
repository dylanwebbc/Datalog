#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton : public Automaton {

  private:
    string toMatch;

  public:
    MatcherAutomaton(string toMatch, TokenType tokenType);
    int Read(const string& input);
    
};

#endif