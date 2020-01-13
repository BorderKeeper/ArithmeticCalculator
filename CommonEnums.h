#pragma once

enum FormulaType {
	FormulaNone,
	Operator,
	Parenthesis,
	Function,
	Number
};

enum OperatorType {
	OperatorNone,
	Addition,
	Substraction,
	Multiplication,
	Division
};

enum ParenthesisType {
	ParenthesisNone,
	Left,
	Right
};

enum FunctionType {
	FunctionNone,
	Negation,
	Sine,
	Cosine,
	Tangent,
	Logarithm,
	Exponential,
	SquareRoot,
	Minimum,
	Maximum,
	GreatestCommonDivisor,
	LeastCommonDenominator
};