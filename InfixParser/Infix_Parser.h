#ifndef INFIX_PARSER_H
#define INFIX_PARSER_H

#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include "Token.h"

using namespace std;

class Infix_Parser
{
private:
	string expression;
public:

	//Constructors
	Infix_Parser();
	Infix_Parser(string exp);

	//Getters and Setters
	string getExpression();
	void setExpression(string exp);

	//Parsing Functions
	string processOperator(istringstream &in, string first, int index);
	int processOperand(istringstream &in, char first);
	vector<Token> parse();
};
#endif