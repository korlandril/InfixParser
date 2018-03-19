#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "Token.h"
#include <stack>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::stack;

class Evaluator
{

private:
	stack<Token> operandStack;
	stack<Token> operatorStack;
	vector<Token> v;
	bool lastOperand = false;

public:
	// Constructors
	Evaluator() { };
	Evaluator(vector<Token> input) { v = input; };


	//Getters and Setters
	vector<Token> getTokens() { return v; };
	void setTokens(vector<Token> _v) { v = _v; };

	//Evaluate function
	int evaluate();

	// Precedence
	int getPrecedence(string _character);

	//Calculate
	Token calculateBinary(Token left, Token opr, Token right);
	Token calculateUnary(Token opr, Token right);
};

#endif