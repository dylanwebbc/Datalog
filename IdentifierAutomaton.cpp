#include "IdentifierAutomaton.h"

IdentifierAutomaton::IdentifierAutomaton(TokenType tokenType) : Automaton(tokenType) {}

//checks if given input is an ID
int IdentifierAutomaton::Read(const string& input) {
  bool isMatch = true;
  int inputRead = 0;
  
  if (isalpha(input[0])) {
    //loops until next character is not alphanumeric
    for (int i = 1; i < (int)input.size() && isMatch; i++) {
      if (!isalnum(input[i])) { //checks it's not alphanumeric
        isMatch = false;
        inputRead = i;
      }
    }
  }

  return inputRead;
}