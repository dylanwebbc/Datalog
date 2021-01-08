#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {

  public:
    CommentAutomaton(TokenType tokenType);
    int Read(const string& input);
    
};

#endif