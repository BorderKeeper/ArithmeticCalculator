#include "PostficCalculator.h"
#include <iostream>

void Exit(const char* error) {
	std::cout << error;
	exit(-1);
}

PostfixCalculator::PostfixCalculator() {
	_solver = new OperationSolver();
	_calculationStack = new Stack<FormulaItem*>();
}

void PostfixCalculator::ValidateResult(FormulaItem* result) {
	if (!_calculationStack->IsEmpty()) {
		Exit("There are still formulas on the stack, equation is incorrect");
	}

	if (result->FormulaType != FormulaType::Number) {
		Exit("Result is not a number, equation is incorrect");
	}

	if (result->Value == INFINITY) {
		Exit("There were issues with the equations, result was infinity.");
	}
}

double PostfixCalculator::Calculate(Stack<FormulaItem*>* postfixStack) {
	while (!postfixStack->IsEmpty()) {
		FormulaItem* item = postfixStack->Pop();

		if (item->FormulaType == FormulaType::Number) {
			_calculationStack->Push(item);
		}
		else if (item->IsProcessable()) {
			ProcessOperation(item);
		}
	}

	FormulaItem* result = _calculationStack->Pop();

	ValidateResult(result);

	return result->Value;
}

void PostfixCalculator::ProcessOperation(FormulaItem* operation) {
	double result = 0;
	
	if (operation->NumberOfParameters() == 1) {
		double value = GetInput();

		result = _solver->SolveSingleParameterFormula(operation, value);
	}

	if (operation->NumberOfParameters() == 2) {
		double secondValue = GetInput();
		double firstValue = GetInput();

		result = _solver->SolveDoubleParameterFormula(operation, firstValue, secondValue);
	}

	_calculationStack->Push(new FormulaItem(result));
}

double PostfixCalculator::GetInput() {
	if (_calculationStack->IsEmpty()) {
		Exit("Formula is incorrect");
	}

	FormulaItem* input = _calculationStack->Pop();

	if (input->FormulaType != FormulaType::Number) {
		Exit("Left side of an equation is not a number");
	}

	return input->Value;
}