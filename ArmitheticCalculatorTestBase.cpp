#include "ArmitheticCalculatorTestBase.h"
#include "ArithmeticCalculator.h"
#include "LinkedList.h"
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

struct Test {
	const char* Equation;	
	double Result;
};

void RunTest(Test test) {
	ArithmeticCalculator* calculator = new ArithmeticCalculator();

	double result = calculator->Solve(_strdup(test.Equation));
	if (fabs(result - test.Result) > 0.001) {
		cout << "WRONG [";
		cout << test.Equation;
		cout << "] should equal [";
		cout << test.Result;
		cout << "] but equals [";
		cout << result;
		cout << "] WRONG";
	}
	else {
		cout << "[";
		cout << test.Equation;
		cout << "] equals [";
		cout << result;
		cout << "]";
	}

	cout << "\n";
}

void ArmitheticCalculatorTest::Run() {
	LinkedList<Test>* testSet = new LinkedList<Test>();
	testSet->Append({ "(2 + sin(3)) * (min(4,5) + 6) * -7", -149.878 });
	testSet->Append({ "0", 0 });
	testSet->Append({ "-5", -5 });
	testSet->Append({ "sin(3)", 0.141 });
	testSet->Append({ "min(4.64,5.1)", 4.64 });
	testSet->Append({ "1+nsd(100,200)", 101 });
	testSet->Append({ "-1+1+nsn(86,128)", 5504 });
	testSet->Append({ "sin(1)+cos(2)+tan(3)", 0.283 });
	testSet->Append({ "cos(2)+(sin(2))+tan(1.4)-1", 5.291 });
	testSet->Append({ "sqrt(2) + exp(5)", 149.827 });
	testSet->Append({ "((1+2)*(3+4))/((5+6)*(7-8))", -1.91 });

	testSet->MoveFirst();
	while (!testSet->AtEnd()) {
		RunTest(testSet->GetCurrent());

		testSet->MoveNext();
	}
}