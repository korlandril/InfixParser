#ifndef TOKEN_H
#include <string>
#include <vector>
using namespace std;
class Token {
	private:
		int opd;
		string opr; 

		vector<string> unary = { "++", "--", "!"};
		vector<string> binary = {"+", "-", "*", "/", "^", "%", ">", ">=", "<", "<=", "==", "!=", "&&", "||"};
		char type;

	public:
		Token(int inopd);
		Token(string inopr);

		int getopd();
		string getopr();

		void setopd(int inopd);
		void setopr(string inopr);

		bool isopd();
		bool isopr();
		bool is_binary();
		bool is_unary();
		

};

#endif

