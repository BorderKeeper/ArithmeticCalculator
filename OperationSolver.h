#pragma once
#include "FormulaItem.h"

class OperationSolver {
private:
	double SolveSingleParameterFunction(FunctionType function, double input);
	double SolveDoubleParameterFunction(FunctionType function, double leftInput, double rightInput);
	double SolveDoubleParameterOperation(OperatorType function, double leftInput, double rightInput);

public:
	double SolveSingleParameterFormula(FormulaItem* formula, double input);
	double SolveDoubleParameterFormula(FormulaItem* formula, double leftInput, double rightInput);
};