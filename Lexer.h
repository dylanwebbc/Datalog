#ifndef LEXER_H
#define LEXER_H

#include "MatcherAutomaton.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include "IdentifierAutomaton.h"
#include "UndefinedAutomaton.h"

class Lexer {
  public:
    vector<Token*> Run(string input);
    Lexer();

  private:
    vector<Token*> tokens;
    vector<Automaton*> automata;
};

#endif