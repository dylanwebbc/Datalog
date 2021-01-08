#include "UndefinedAutomaton.h"

UndefinedAutomaton::UndefinedAutomaton(TokenType tokenType) : Automaton(tokenType) {}

//returns undefined if all other Automatons fail
int UndefinedAutomaton::Read(const string& input) {
  int inputRead = 1;
  bool isMatch = true;
  newLines = 0;

  //checks for newlines
  if (input[0] == '\n') {
    newLines = 1;
  }

  //checks for bad strings
  if (input[0] == '\'') {
    for (int i = 1; i < (int)input.size() && isMatch; i++) {
      if (input[i] == '\'') { //checks for completion of string
        if (i < (int)input.size() - 1) {//only checks for apostrophe before eof
          if (input[i+1] != '\'') {
            isMatch = false;
          }
          else {//if it's just an apostrophe
            i += 1;
          }
        }
        else {
          isMatch = false;
        }
      }
      else if (input[i] == '\n') { //checks for newlines
        newLines += 1;
      }
    }

    if (isMatch) {
      inputRead = (int)input.size();
      //removes extra newline from very end
      if (input[(int)input.size() - 1] == '\n') {
        inputRead -= 1;
        newLines -= 1;
      }
    }
  }

  //checks for bad multiline comments
  if (input[0] == '#' && input[1] == '|') {
    for (int i = 1; i < (int)input.size() && isMatch; i++) {
      if (input[i] == '|') { //checks for completion of comment
        if (i < (int)input.size() - 1) {//only checks for end of comment before eof
          if (input[i+1] == '#') {
            isMatch = false;
          }
        }
      }
      else if (input[i] == '\n') { //checks for newlines
        newLines += 1;
      }
    }

    if (isMatch) {
      inputRead = (int)input.size();
      //removes extra newline from very end
      if (input[(int)input.size() - 1] == '\n') {
        inputRead -= 1;
        newLines -= 1;
      }
    }
  }

  return inputRead;
}