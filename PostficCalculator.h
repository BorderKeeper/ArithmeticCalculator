#pragma once

#include "Stack.h";
#include "FormulaItem.h"
#include "OperationSolver.h"

class PostfixCalculator {
private:
	Stack<FormulaItem*>* _calculationStack;
	OperationSolver* _solver;
	void ProcessOperation(FormulaItem* operation);
	double GetInput();
	void ValidateResult(FormulaItem* result);
public:
	PostfixCalculator();
	double Calculate(Stack<FormulaItem*>* postfixStack);
};