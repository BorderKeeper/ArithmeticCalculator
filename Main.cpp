#include <iostream>
#include "ArithmeticCalculator.h"
#include "ArmitheticCalculatorTestBase.h"

#define TEST true

using namespace std;

void ValidateInput(int argc, char* argv[]) {
	if (argc != 2) {
		exit(-1);
	}
}

int main(int argc, char* argv[])
{
	if (!TEST) {
		ValidateInput(argc, argv);

		ArithmeticCalculator* calculator = new ArithmeticCalculator();

		double result = calculator->Solve(argv[1]);

		cout << "Result is: ";
		cout << result;
	} else {
		ArmitheticCalculatorTest* unitTest = new ArmitheticCalculatorTest();

		unitTest->Run();
	}

	return 0;
}