#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(string toMatch, TokenType tokenType) : Automaton(tokenType) {
  this->toMatch = toMatch;
}

//checks if the given input matches the symbol
int MatcherAutomaton::Read(const string& input) {
  bool isMatch = true;
  int inputRead = 0;
  for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
    if (input[i] != toMatch[i]) {
      isMatch = false;
    }
  }
  if (isMatch) {
    inputRead = (int)toMatch.size();
  }
  return inputRead;
}