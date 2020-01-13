#include "FormulaItem.h"

FormulaItem::FormulaItem() {
	FormulaType = FormulaType::FormulaNone;
	SelectedParenthesis = ParenthesisType::ParenthesisNone;
	SelectedOperator = OperatorType::OperatorNone;
	SelectedFunction = FunctionType::FunctionNone;
	Value = -1;
}

FormulaItem::FormulaItem(OperatorType op) {
	FormulaItem();
	FormulaType = FormulaType::Operator;
	SelectedOperator = op;
	Value = -1;
};

FormulaItem::FormulaItem(ParenthesisType par) {
	FormulaItem();
	FormulaType = FormulaType::Parenthesis;
	SelectedParenthesis = par;
};

FormulaItem::FormulaItem(FunctionType fun) {
	FormulaItem();
	FormulaType = FormulaType::Function;
	SelectedFunction = fun;
};

FormulaItem::FormulaItem(double value) {
	FormulaItem();
	FormulaType = FormulaType::Number;
	Value = value;
};

bool FormulaItem::IsOneParameterFunction() {
	return
		SelectedFunction == FunctionType::Cosine ||
		SelectedFunction == FunctionType::Sine ||
		SelectedFunction == FunctionType::SquareRoot ||
		SelectedFunction == FunctionType::Tangent ||
		SelectedFunction == FunctionType::Negation ||
		SelectedFunction == FunctionType::Logarithm ||
		SelectedFunction == FunctionType::Exponential;
}

int FormulaItem::NumberOfParameters() {
	if (FormulaType != FormulaType::Operator && IsOneParameterFunction()) {
		return 1;
	}

	return 2; //all other operations and functions are two
}

int FormulaItem::GetPriority() {
	if (FormulaType == FormulaType::Number) {
		return 0;
	}
		
	if (FormulaType == FormulaType::Operator) {
		if (SelectedOperator == OperatorType::Addition || SelectedOperator == OperatorType::Substraction) {
			return 1;
		}

		if (SelectedOperator == OperatorType::Multiplication || SelectedOperator == OperatorType::Division) {
			return 2;
		}
	}

	if (FormulaType == FormulaType::Function) {
		if (SelectedFunction != FunctionType::Negation) {
			if (!IsOneParameterFunction()) {
				return 3;
			} else {
				return 4;
			}
		} else {
			return 5;
		}
	}

	if (IsLeftParenthesis() || IsRightParenthesis()) {
		return 6;
	}

	return -1;
}

bool FormulaItem::IsProcessable() {
	return FormulaType == FormulaType::Function ||
		FormulaType == FormulaType::Operator ||
		FormulaType == FormulaType::Parenthesis;
}

bool FormulaItem::IsLeftParenthesis() {
	return FormulaType == FormulaType::Parenthesis && SelectedParenthesis == ParenthesisType::Left;
}

bool FormulaItem::IsRightParenthesis() {
	return FormulaType == FormulaType::Parenthesis && SelectedParenthesis == ParenthesisType::Right;
}

std::string FormulaItem::ToString() {
	switch (FormulaType)
	{
		case Operator:
			switch (SelectedOperator)
			{
				case Addition:
					return "+";
				case Substraction:
					return "-";
				case Multiplication:
					return "*";
				case Division:
					return "/";
			}
		case Parenthesis:
			switch (SelectedParenthesis)
			{
				case Left:
					return "(";
				case Right:
					return ")";
			}
		case Function:
			switch (SelectedFunction)
			{
				case Negation:
					return "neg";
				case Sine:
					return "sin";
				case Cosine:
					return "cos";
				case Tangent:
					return "tan";
				case Logarithm:
					return "log";
				case Exponential:
					return "exp";
				case SquareRoot:
					return "sqrt";
				case Minimum:
					return "min";
				case Maximum:
					return "max";
				case GreatestCommonDivisor:
					return "nsn";
				case LeastCommonDenominator:
					return "nsd";
			}
		case Number:
			return std::to_string(Value);
	}
}