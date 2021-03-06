#include "Evaluator.h"
#include "Parser.h"
#include <iostream>

using namespace std;

int Evaluator::evaluate()
{
	int index = 0;

	// Error detection
	if (v[0].getopr() == ")")
	{
		cout << "Cannot begin with a ) character! " << index << endl;
		exit(0);
	}

	else if (v[0].getopr() != "" && v[0].isBinary())
	{
		cout << "Cannot begin with binary character! " << index << endl;
		exit(0);
	}

	for (vector<Token>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		vector<Token>::iterator nextCharacter = iter;
		nextCharacter++;
		if (iter->getopr() == "/" && nextCharacter->getopr() == "" && nextCharacter->getopd() == 0)
		{
			cout << "You cannot divide by zero! " << index << endl;
			exit(0);
		}

		// If the character is an operand then push to the operand stack
		if (iter->getopr() == "" && !lastOperand)
		{
			operandStack.push(*iter);
			lastOperand = true;

			while (!operatorStack.empty())
			{
				if (operatorStack.empty() || operandStack.empty())
				{
					cout << "Either the operator stack is empty or the operand stack is empty" << index << endl;
					exit(0);
				}
				// If the top of the operator stack has a unary operator than continue to calculate unary operators
				if (operatorStack.top().isUnary())
				{
					Token opr, right;
					opr = operatorStack.top();
					operatorStack.pop();
					right = operandStack.top();
					operandStack.pop();
					operandStack.push(calculateUnary(opr, right));
				}
				else
				{
					break;
				}
			}
		}
		// Error checking to see if there are two operands
		else if (iter->getopr() == "" && lastOperand)
		{
			cout << "There cannot be two operands back to back. " << index << endl;
			exit(0);
		}
		else if (iter->getopr() == "(")
		{
			// If the previous number was an operand then multiply
			if (lastOperand)
			{
				Token multiply;
				multiply.setopr("*");
				operatorStack.push(multiply);
			}
			operatorStack.push(*iter);
			lastOperand = false;
		}
		else if (iter->getopr() != "" && lastOperand && iter->isBinary())
		{
			if (operatorStack.empty())
			{
				operatorStack.push(*iter);
				lastOperand = false;
			}

			//The check the precedence of current token compared to the top of the operatorStack
			else if (getPrecedence(iter->getopr()) > getPrecedence(operatorStack.top().getopr()))
			{
				operatorStack.push(*iter);
				lastOperand = false;
			}
			else if (getPrecedence(iter->getopr()) <= getPrecedence(operatorStack.top().getopr()))
			{
				// If the top of the operator stack has precedence over or equal to then calculateBinary
				if (operatorStack.empty() || operandStack.empty())
				{
					cout << "At least one of the stacks are empty. " << index << endl;
					exit(0);
				}
				Token left, opr, right;
				right = operandStack.top();
				operandStack.pop();
				left = operandStack.top();
				operandStack.pop();
				opr = operatorStack.top();
				operatorStack.pop();
				operandStack.push(calculateBinary(left, opr, right));
				operatorStack.push(*iter);
				lastOperand = false;
			}
		}

		else if (iter->getopr() != "" && !lastOperand && iter->isBinary())
		{
			cout << "You cannot have two binary operators back to back. " << index << endl;
			exit(0);
		}

		// Push the unarys from operatorStack
		else if (iter->getopr() != "" && iter->isUnary())
		{
			if (nextCharacter != v.end())
			{
				// If it's binary
				if (nextCharacter->getopr() != "" && nextCharacter->isBinary())
				{
					cout << "There cannot be a unary then binary operator back to back. " << index << endl;
					exit(0);
				}
				//If it's unary, push it to the operator stack
				else if (nextCharacter->getopr() != "" && nextCharacter->isUnary())
				{
					operatorStack.push(*iter);
				}
				else if (nextCharacter->getopr() == "")
				{
					operatorStack.push(*iter);
				}
				else
				{
					cout << "A number or a unary operator did now come after a unary operator. " << index << endl;
					exit(0);
				}
			}
		}
		// If precedence dominates then calculate until ')' is found.
		else if (iter->getopr() == ")") {
			while (!operatorStack.empty())
			{
				if (operatorStack.empty())
				{
					cout << "There was no ')' found. The stack is empty. " << index << endl;
					exit(0);
				}
				if (operatorStack.top().getopr() != "(")
				{
					Token left, opr, right;
					right = operandStack.top();
					operandStack.pop();
					left = operandStack.top();
					operandStack.pop();
					opr = operatorStack.top();
					operatorStack.pop();
					operandStack.push(calculateBinary(left, opr, right));
				}
				else
				{
					break;
				}
			}
			operatorStack.pop();
			lastOperand = true;

		}
		index += 1;
	}
	// Calculate until only one is left in the operand stack
	while (!operatorStack.empty())
	{
		Token left, opr, right;
		right = operandStack.top();
		operandStack.pop();
		left = operandStack.top();
		operandStack.pop();
		opr = operatorStack.top();
		operatorStack.pop();

		operandStack.push(calculateBinary(left, opr, right));
	}
	int result = operandStack.top().getopd();
	operandStack.pop();

	//This checks to see if something messed up
	if (!operandStack.empty())
	{
		cout << "The operand stack is not empty." << index << endl;
		exit(0);
	}
	return result;

}
