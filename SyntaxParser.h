#pragma once

#include <string>
#include "LinkedList.h"
#include "Stack.h"
#include "FormulaItem.h"

using namespace std;

class SyntaxParser {
private:
	string _input;
	int _current;
	LinkedList<FormulaItem*>* _parsedExpression;
	char GetNextChar();
	void RewindByOne();
	void ParseText();
	void ParseNumber();
public:
	SyntaxParser();
	~SyntaxParser();
	LinkedList<FormulaItem*>* ParseExpression(string input);
};