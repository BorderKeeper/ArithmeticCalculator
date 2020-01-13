#include "ArithmeticCalculator.h"
#include "SyntaxParser.h"
#include "PostfixConvertor.h"
#include "PostficCalculator.h"

double ArithmeticCalculator::Solve(char* equation) {
	SyntaxParser* parser = new SyntaxParser(equation);
	PostfixConvertor* postfixConverter = new PostfixConvertor();
	PostfixCalculator* postfixCalculator = new PostfixCalculator();

	LinkedList<FormulaItem*>* formulaList = parser->ParseExpression();

	Stack<FormulaItem*>* postfixStack = postfixConverter->CreatePostfixStack(formulaList);

	double result = postfixCalculator->Calculate(postfixStack);

	return result;
}