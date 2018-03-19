#include "Infix_Parser.h"

//Default Constructor
Infix_Parser::Infix_Parser()
{
	expression = "";
}

//Non-default Constructor
Infix_Parser::Infix_Parser(string exp)
{
	expression = exp;
}

//Returns the infix expression
string Infix_Parser::getExpression()
{
	return expression;
}

//Sets the infix expression
void Infix_Parser::setExpression(string exp)
{
	expression = exp;
}

//Reads in and returns the processed operator
string Infix_Parser::processOperator(istringstream &in, string first, int index)
{
	string opr = first;
	string next = "";
	in >> next;

	//Processing 2-character operators with the same characters
	if (next == opr)
	{
		opr += next;	//Appends the second operator character to the operator string
		return opr;
	}
	//Processing 2-character operators of different characters
	else if ((opr == "!" && next == "=") || (opr == "<" && next == "=") || (opr == ">" && next == "="))
	{
		opr += next;
		return opr;
	}

	char op = next.at(0);	//Converts next into a char that can be put back into the read-in expression
	in.putback(op);
	return opr;
}

//Reads in and returns the processed operand
int Infix_Parser::processOperand(istringstream &in, char first)
{
	//Reads in operands of multiple characters
	int value;
	in.putback(first);
	in >> value;
	return value;
}

//Parses the expression
vector<Token> Infix_Parser::parse()
{
	//Initialized Variables
	vector<Token> v;
	istringstream temp(expression);
	int index = 0;
	char next = ' ';
	char prev = ' ';

	//Reading in the expression
	while (temp >> next)
	{
		char next_next = temp.peek();

		//Checking for spaces
		if (isspace(next))
		{
			continue;
		}
		//Checking for operands
		else if (isdigit(next))
		{
			Token t(Infix_Parser::processOperand(temp, next));
			v.push_back(t);
		}
		//Checking for single-character operators
		else if (next == '-' && v.empty())
		{
			Token t('-');
			v.push_back(t);
		}
		else if (!isdigit(prev) && next == '-')
		{
			Token t('-');
			v.push_back(t);
		}
		else if (next == '>')
		{
			Token t(Infix_Parser::processOperator(temp, ">", index));
			v.push_back(t);
		}
		else if (next == '<')
		{
			Token t(Infix_Parser::processOperator(temp, "<", index));
			v.push_back(t);
		}
		else if (next == '!')
		{
			Token t(Infix_Parser::processOperator(temp, "!", index));
			v.push_back(t);
		}
		//Checking for 2-character operators
		else if (next == '-' && next_next == '-')
		{
			Token t(Infix_Parser::processOperator(temp, "-", index));
			v.push_back(t);
		}
		else if (next == '+' && next_next == '+')
		{
			Token t(Infix_Parser::processOperator(temp, "+", index));
		}
		else if (next == '&' && next_next == '&&')
		{
			Token t(Infix_Parser::processOperator(temp, "&", index));
			v.push_back(t);
		}
		else if (next == '|' && next_next == '|')
		{
			Token t(Infix_Parser::processOperator(temp, "|", index));
			v.push_back(t);
		}

		else if (next == '=' && next_next == '=')
		{
			Token t(Infix_Parser::processOperator(temp, "=", index));
			v.push_back(t);
		}
		else
		{
			Token t(next);
			v.push_back(t);
		}

		prev = next;
		index++;
	}
	return v;
}