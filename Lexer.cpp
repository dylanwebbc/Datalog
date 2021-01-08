#include "Lexer.h"

Lexer::Lexer() { //create vector of automatons
  automata.push_back(new MatcherAutomaton(",", COMMA));
  automata.push_back(new MatcherAutomaton(".", PERIOD));
  automata.push_back(new MatcherAutomaton("?", Q_MARK));
  automata.push_back(new MatcherAutomaton("(", LEFT_PAREN));
  automata.push_back(new MatcherAutomaton(")", RIGHT_PAREN));
  automata.push_back(new MatcherAutomaton(":", COLON));
  automata.push_back(new MatcherAutomaton(":-", COLON_DASH));
  automata.push_back(new MatcherAutomaton("*", MULTIPLY));
  automata.push_back(new MatcherAutomaton("+", ADD));
  automata.push_back(new MatcherAutomaton("Schemes", SCHEMES));
  automata.push_back(new MatcherAutomaton("Facts", FACTS));
  automata.push_back(new MatcherAutomaton("Rules", RULES));
  automata.push_back(new MatcherAutomaton("Queries", QUERIES));
  automata.push_back(new CommentAutomaton(COMMENT));
  automata.push_back(new StringAutomaton(STRING));
  automata.push_back(new IdentifierAutomaton(ID));
  automata.push_back(new UndefinedAutomaton(UNDEFINED));
}

vector<Token*> Lexer::Run(string input) {
  
  //Automaton* newAutomata = nullptr;
  
  int lineNum = 1;
  
  //loops through input and creates tokens for every viable string
  while (input.size() > 0) {
    int maxRead = 0;
    int inputRead = 0;
    int maxNewLines = 0;
    Automaton* maxAutomaton = automata.at(0);

    
    //loops through each automata
    for (unsigned int j = 0; j < automata.size(); ++j ) {
      inputRead = (*automata.at(j)).Read(input);
      
      //reads up to maxRead
      if (inputRead > maxRead) {
        maxRead = inputRead;
        maxAutomaton = automata.at(j);
        maxNewLines = (*automata.at(j)).NewLinesRead();
      }
    }

    //if an automaton accepts the input, add the token to our vector
    if (maxRead > 0) {
      //only add non-whitespace tokens
      if (input[0] != ' ' && input[0] != '\n' && input[0] != '\t') {
        Token* newToken = (*maxAutomaton).CreateToken(input.substr(0, maxRead), lineNum);
        if (newToken->getType() != COMMENT) {
          tokens.push_back(newToken);
        }
      }

      lineNum += maxNewLines;
    }
    /*else { // No automaton accepted the input, so it is invalid
      maxRead = 1;
      Token* newToken = new Token(UNDEFINED, to_string(input.at(i)), lineNum);
      tokens.push_back(newToken);
    }*/
    input.erase(0, maxRead);
  }
  //add an end of file token
  Token* newToken = new Token(EOFILE, "", lineNum - 1);
  tokens.push_back(newToken);

  return tokens;
}