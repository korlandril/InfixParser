#include "Token.h"
#include <string>
#include <algorithm>
using namespace std;


Token::Token(int inopd) // Constructor with an initialized operand
{
	opd = inopd;
	opr = "";
}

Token::Token(string inopr) // Constructor with an intialized operator
{
	opr = inopr;
	opd = NULL;
}

int Token::getopd() // Return operand
{
	return opd;
}

string Token::getopr() // Return operator
{
	return opr;
}

void Token::setopd(int inopd) // Set Operand
{
	opd = inopd;
}

void Token::setopr(string inopr) // Set Operator
{
	opr = inopr;
}

bool Token::isopd() // Return true if the Token is an operand
{
	if (opd != NULL)
	{
		return true;
	}

	return false;
}

bool Token::isopr() // Return true if the Token is an operator
{
	if (opr.length() != 0) {
		return true;
	}
	return false;
}

bool Token::isBinary() // Return true if the Token is a binary operator
{

	//Iterate through the vector of binary operators to determine if the token matches any of them
	vector<string>::iterator it;
	it = find(binary.begin(), binary.end(), opr);
	if (it != binary.end())
		return true;
	else
		return false;

}

bool Token::isUnary() // Return true if the Token is a Unary Operator
{
	//Iterate through the vector of unary operators to determine if the token matches any of them
	vector<string>::iterator it;
	it = find(unary.begin(), unary.end(), opr);
	if (it != unary.end())
		return true;
	else
		return false;
}