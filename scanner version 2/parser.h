#pragma once
#include<string>
#include <iomanip>
#include <stack>
#include "scanner.h"
class parser
{
private:
	scanner scan;
	std::vector <std::pair< std::string, std::pair< std::string, std::string>>> result;
	int index;
	std::stack<bool> flagIf;
	bool checkStmtSequence();
	bool checkStatement();
	bool checkIfStmt();
	bool checkRepeatStmt();
	bool checkAssignStmt();
	bool checkReadStmt();
	bool checkWriteStmt();
	bool match(std::string word);
	bool exp();
	bool checkComparisonOp ();
	bool checkSimpleExp();
	bool checkAddop();
	bool checkTerm();
	bool checkmulop();
	bool checkfactor();
	bool matchSecond(std::string word);
	bool matchEnd();

public :
	parser();
	void readFromFile(std::string path);

};

