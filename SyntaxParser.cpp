#include "SyntaxParser.h"
#include "ListToDoubleConverter.h"
#include <iostream>

using namespace std;

SyntaxParser::SyntaxParser() {
	_parsedExpression = new LinkedList<FormulaItem*>();
	_current = 0;
}

SyntaxParser::~SyntaxParser() {
	delete _parsedExpression;
};

bool IsDecimalNumber(char c) {
	return (c >= '0' && c <= '9') || c == '.';
}

bool IsSpace(char c) {
	return c == ' ' || c == '\n' || c == '\n\r' || c == '\r';
}

bool IsText(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

void Exit(string error) {
	cout << error;
	exit(-1);
}

bool StringCompare(LinkedList<char>* list, string s) {
	list->MoveFirst();
	int counter = 0;
	while (!list->AtEnd()) {
		if (counter >= s.length()) {
			return false;
		}

		if (list->GetCurrent() != s[counter]) {
			return false;
		}

		counter++;
		list->MoveNext();
	}

	return true;
}

void AppendFunction(LinkedList<FormulaItem*>* _parsedExpression, LinkedList<char>* buffer) {
	/*sin, cos, tan, log, exp, sqrt, min, max, nsd, nsn*/
	if (StringCompare(buffer, "sin")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Sine));
	} else if (StringCompare(buffer, "cos")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Cosine));
	} else if (StringCompare(buffer, "tan")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Tangent));
	} else if (StringCompare(buffer, "log")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Logarithm));
	} else if (StringCompare(buffer, "exp")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Exponential));
	} else if (StringCompare(buffer, "sqrt")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::SquareRoot));
	} else if (StringCompare(buffer, "min")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Minimum));
	} else if (StringCompare(buffer, "max")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::Maximum));
	} else if (StringCompare(buffer, "nsd")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::GreatestCommonDivisor));
	} else if (StringCompare(buffer, "nsn")) {
		_parsedExpression->Append(new FormulaItem(FunctionType::LeastCommonDenominator));
	} else {
		Exit("Function not recognised");
	}
}

void SyntaxParser::ParseText() {
	LinkedList<char>* buffer = new LinkedList<char>();
	RewindByOne();

	//Checking for function names terminated by either open parenthesis
	char c;
	while (true) {
		c = GetNextChar();

		if (IsText(c)) {
			buffer->Append(c);
		} else if (c == '(') {
			AppendFunction(_parsedExpression, buffer);
			break;
		} else {
			Exit("Function not followed by open parenthesis");
		}
	}

	RewindByOne();
	delete buffer;
}

void SyntaxParser::ParseNumber() {
	LinkedList<char>* buffer = new LinkedList<char>();
	RewindByOne();

	char c;
	while (true) {
		c = GetNextChar();

		if (IsDecimalNumber(c)) {
			buffer->Append(c);
		} else {
			break;
		}
	}

	float value = ConvertCharListToDouble(buffer);
	_parsedExpression->Append(new FormulaItem(value));

	RewindByOne();
	delete buffer;
}

LinkedList<FormulaItem*>* SyntaxParser::ParseExpression(string input) {
	_input = input;

	while (true) {
		char c = GetNextChar();

		if (c == '\0') {
			return _parsedExpression;
		} else if (IsText(c)) {
			ParseText();
		} else if (IsDecimalNumber(c)) {
			ParseNumber();
		} else if (IsSpace(c)) {
			continue;
		} else if (c == '(') {
			_parsedExpression->Append(new FormulaItem(ParenthesisType::Left));
		} else if (c == ')') {
			_parsedExpression->Append(new FormulaItem(ParenthesisType::Right));
		} else if (c == '+') {
			_parsedExpression->Append(new FormulaItem(OperatorType::Addition));
		} else if (c == '-') {
			if (_parsedExpression->IsEmpty() || _parsedExpression->Last()->FormulaType == FormulaType::Operator) {
				_parsedExpression->Append(new FormulaItem(FunctionType::Negation));
			} else {
				_parsedExpression->Append(new FormulaItem(OperatorType::Substraction));
			}		
		} else if (c == '*') {
			_parsedExpression->Append(new FormulaItem(OperatorType::Multiplication));
		} else if (c == '/') {
			_parsedExpression->Append(new FormulaItem(OperatorType::Division));
		} else if (c == ',') {
			//max(1+2,3+4) -> max(1+2)(3+4)
			_parsedExpression->Append(new FormulaItem(ParenthesisType::Right));
			_parsedExpression->Append(new FormulaItem(ParenthesisType::Left));
		} else {
			Exit("Not recognised character in equation");
		}		
	}
}

char SyntaxParser::GetNextChar() {
	if (_current >= _input.length()) {
		_current++;
		return '\0';		
	}

	char result = _input[_current];
	_current++;

	return result;
}

void SyntaxParser::RewindByOne() {
	_current--;
}