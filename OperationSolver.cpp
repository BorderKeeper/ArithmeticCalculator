#include "OperationSolver.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

double CalculateGreatestCommonDivisor(double a, double b)
{
	if (a < b) {
		return CalculateGreatestCommonDivisor(b, a);
	}

	if (fabs(b) < 0.001) {
		return a;
	} else {
		return (CalculateGreatestCommonDivisor(b, a - floor(a / b) * b));
	}
}

double CalculateLeastCommonDenominator(double a, double b) {
	return (a * b) / CalculateGreatestCommonDivisor(a, b);
}

double OperationSolver::SolveSingleParameterFormula(FormulaItem* formula, double input) {
	if (formula->FormulaType == FormulaType::Function) {
		return SolveSingleParameterFunction(formula->SelectedFunction, input);
	}
	
	if(formula->FormulaType == FormulaType::Operator) {
		return INFINITY;
	}
}

double OperationSolver::SolveDoubleParameterFormula(FormulaItem* formula, double leftInput, double rightInput) {
	if (formula->FormulaType == FormulaType::Function) {
		return SolveDoubleParameterFunction(formula->SelectedFunction, leftInput, rightInput);
	}

	if (formula->FormulaType == FormulaType::Operator) {
		return SolveDoubleParameterOperation(formula->SelectedOperator, leftInput, rightInput);
	}
}

double OperationSolver::SolveSingleParameterFunction(FunctionType function, double input) {
	switch (function)
	{
		case Negation:
			return -input;
		case Sine:
			return sin(input);
		case Cosine:
			return cos(input);
		case Tangent:
			return tan(input);
		case Logarithm:
			return log(input);
		case Exponential:
			return exp(input);
		case SquareRoot:
			return sqrt(input);
	}

	return INFINITY;
}

double OperationSolver::SolveDoubleParameterFunction(FunctionType function, double leftInput, double rightInput) {
	switch (function)
	{
		case Minimum:
			return fmin(leftInput, rightInput);
		case Maximum:
			return fmax(leftInput, rightInput);
		case GreatestCommonDivisor:
			return CalculateGreatestCommonDivisor(leftInput, rightInput);
		case LeastCommonDenominator:
			return CalculateLeastCommonDenominator(leftInput, rightInput);
	}

	return INFINITY;
}

double OperationSolver::SolveDoubleParameterOperation(OperatorType op, double leftInput, double rightInput) {
	switch (op)
	{
		case Addition:
			return leftInput + rightInput;
		case Substraction:
			return leftInput - rightInput;
		case Multiplication:
			return leftInput * rightInput;
		case Division:
			return leftInput / rightInput;
	}

	return INFINITY;
}