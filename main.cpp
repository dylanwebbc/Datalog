#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

#include <fstream>

int main(int argc, char *argv[]) {
	string filename = argv[1];
	string line;
	string input;

  Lexer lexer;
  Parser parser;
	vector<Token *> tokens;

	ifstream fin;
	fin.open(filename);
	// loop until EOF
	while (fin) {
		getline(fin, line);
		input = (input + line + '\n'); // add all info to one string
	}
	fin.close();

	// cout << input; //to test if input being read correctly

	// generate tokens from input using Lexer class
	tokens = lexer.Run(input);

	// loop through tokens and convert them to strings and print
	/*for (unsigned int i = 0; i < tokens.size(); ++i) {
		cout << (*tokens.at(i)).toString() << endl;
	}
	cout << "Total Tokens = " << tokens.size() << endl;*/

  DatalogProgram datalog = parser.Parse(tokens);

  //cout << datalog.toString();

  Interpreter interpreter(datalog);
  interpreter.evaluateRules();
  interpreter.evaluateQueries();

  /*//output result to a .txt file
	ofstream fout;
	string newFilename = "out" + filename.substr(2, filename.length() - 1);
	fout.open("FilesOut/" + newFilename);

  fout << ***OUTPUT***

	fout.close();*/

	return 0;
}