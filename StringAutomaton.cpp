#include "StringAutomaton.h"

StringAutomaton::StringAutomaton(TokenType tokenType) : Automaton(tokenType) {}

//checks if given input is a string
int StringAutomaton::Read(const string& input) {
  bool isMatch = true;
  int inputRead = 0;
  newLines = 0;
  
  if (input[0] == '\'') {
    //loops until another single quote is found
    for (int i = 1; i < (int)input.size() && isMatch; i++) {
      if (input[i] == '\'') {//checks for apostrophes
        if (i < (int)input.size() - 1) {//only double checks before eof 
          if (input[i+1] != '\'') {
            isMatch = false;
            inputRead = i + 1;
          }
          else {//if it's an apostrophe
            i += 1;
          }
        }
        else {
          isMatch = false;
          inputRead = i + 1;
        }
      }
      else if (input[i] == '\n') { //checks for newlines
        newLines += 1;
      }
    }
  }

  return inputRead;
}