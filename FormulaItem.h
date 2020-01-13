#pragma once

#include "CommonEnums.h"
#include <string>

class FormulaItem {
public:
	FormulaType FormulaType;
	OperatorType SelectedOperator;
	ParenthesisType SelectedParenthesis;
	FunctionType SelectedFunction;
	double Value;
	FormulaItem();
	FormulaItem(OperatorType op);
	FormulaItem(ParenthesisType par);
	FormulaItem(FunctionType fun);
	FormulaItem(double value);
	int GetPriority();
	bool IsProcessable();
	bool IsLeftParenthesis();
	bool IsRightParenthesis();
	bool IsOneParameterFunction();
	int NumberOfParameters();
	std::string ToString();
};