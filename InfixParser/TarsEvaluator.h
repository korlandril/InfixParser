#ifndef TARSEVALUATOR_H
#define TARSEVALUATOR_H

#include "Token.h"
#include "Infix_Parser.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Evaluator {
	private:
		vector<Token> tokens;
		stack<Token> operands;
		stack<Token> operators;

		bool isLastNum = false;

	public:
		//Constructors
		Evaluator() {};
		Evaluator(vector<Token> inToken) { tokens = inToken; };

		//Setters
		void setTokens(vector<Token> tokens); 

		int precedence(string op_to_check);

		int eval();

		Token binaryOperation(Token left, Token opr, Token right);
		Token unaryOperation(Token opr, Token right);



};


#endif