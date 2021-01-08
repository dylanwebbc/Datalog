#include "CommentAutomaton.h"

CommentAutomaton::CommentAutomaton(TokenType tokenType) : Automaton(tokenType) {}

//checks if given input is a comment
int CommentAutomaton::Read(const string& input) {
  bool isMatch = true;
  int inputRead = 0;
  newLines = 0;
  
  if (input[0] == '#') {

    if (input.size() > 1) {
      //multiline comment
      if (input[1] == '|') {
        //loops until multiline comment ends
        for (int i = 2; i < (int)input.size() && isMatch; i++) {
          if (input[i] == '|' && input[i+1] == '#') {
            isMatch = false;
            inputRead = i + 2;
          }
          else if (input[i] == '\n') { //checks for newlines
            newLines += 1;
          }
        }
      }
      //line comment
      else {
        //loops until end of line
        for (int i = 1; i < (int)input.size() && isMatch; i++) {
          if (input[i] == '\n') {
            isMatch = false;
            inputRead = i;
          }
        }
      }
    }
    else {
      inputRead = 1;
    }
  }

  return inputRead;
}