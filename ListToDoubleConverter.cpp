#include "ListToDoubleConverter.h"
#include <stdlib.h>
#include <math.h>

double ConvertCharListToDouble(LinkedList<char>* list) {
	LinkedList<int>* leftSide = new LinkedList<int>();
	LinkedList<int>* rightSide = new LinkedList<int>();

	bool hitADot = false;
	list->MoveFirst();
	while (!list->AtEnd()) {
		if (list->GetCurrent() == '.') {
			if (hitADot) {
				exit(-1);
			}
			
			hitADot = true;
		}
		else if(list->GetCurrent() >= '0' && list->GetCurrent() <= '9') {
			if (!hitADot) {
				leftSide->Append(list->GetCurrent() - '0');
			}
			else {
				rightSide->Append(list->GetCurrent() - '0');
			}
		}

		list->MoveNext();
	}

	double value = 0;

	leftSide->MoveFirst();
	int leftSidePower = leftSide->Length() - 1;
	while (!leftSide->AtEnd()) {

		value += leftSide->GetCurrent() * pow(10, leftSidePower);

		leftSidePower--;
		leftSide->MoveNext();
	}

	rightSide->MoveFirst();
	int rightSidePower = 1;
	while (!rightSide->AtEnd()) {

		value += rightSide->GetCurrent() * pow(10, -rightSidePower);

		rightSidePower++;
		rightSide->MoveNext();
	}

	delete leftSide;
	delete rightSide;

	return value;
}