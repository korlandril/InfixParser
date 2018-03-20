//Yes I know my code isn't documented at all srry srry 

#ifndef TOKEN_H
#include <string>
#include <vector>
using namespace std;
class Token {
	private:
		int opd = NULL;
		string opr = NULL; 

		vector<string> unary = { "++", "--", "!"};
		vector<string> binary = {"+", "-", "*", "/", "^", "%", ">", ">=", "<", "<=", "==", "!=", "&&", "||"};
		char type;

	public:
		Token() {};
		Token(int inopd);
		Token(string inopr);

		int getopd();
		string getopr();

		void setopd(int inopd);
		void setopr(string inopr);

		bool isopd(); //Checks if Token is an oeprand
		bool isopr(); //Checks if the token is an operator
		bool isBinary(); //Checks if the Token is a Binary operator
		bool isUnary(); //Checks if the Token is a Unary Operator
		

};

#endif

