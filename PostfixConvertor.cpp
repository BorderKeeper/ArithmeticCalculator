#include "PostfixConvertor.h"
#include "Stack.h"

Stack<FormulaItem*>* PostfixConvertor::CreatePostfixStack(LinkedList<FormulaItem*>* formulaList) {
	Stack<FormulaItem*>* operandStack = new Stack<FormulaItem*>();
	Stack<FormulaItem*>* outputStack = new Stack<FormulaItem*>();

	formulaList->MoveFirst();
	while (!formulaList->AtEnd()) {
		FormulaItem* item = formulaList->GetCurrent();

		if (item->FormulaType == FormulaType::Number) {
			outputStack->Push(item);
		}
		else if (item->IsProcessable()) {

			//Pop the stack until you find a symbol of lower priority number than the current one. 
			//An incoming left parenthesis will be considered to have higher priority than any other symbol. 
			//A left parenthesis on the stack will not be removed unless an incoming right parenthesis is found. 
			//The popped stack elements will be written to output.
			while (!operandStack->IsEmpty() && operandStack->Peek()->GetPriority() > item->GetPriority()) {
				if (operandStack->Peek()->IsLeftParenthesis()) {
					break;
				} else {
					FormulaItem* poppedOperand = operandStack->Pop();
					outputStack->Push(poppedOperand);
					break;
				}
			}

			//If a right parenthesis is the current symbol, pop the stack down to(and including) the first left parenthesis.
			//Write all the symbols except the left parenthesis to the output(i.e.write the operators to the output).
			if (item->IsRightParenthesis()) {
				while (!operandStack->IsEmpty()) {
					FormulaItem* poppedOperand = operandStack->Pop();

					if (poppedOperand->FormulaType != FormulaType::Parenthesis) {
						outputStack->Push(poppedOperand);
					}

					//Remove the left parenthesis we hit and stop
					if (poppedOperand->IsLeftParenthesis()) {
						break;
					}
				}
			}
			else {
				operandStack->Push(item);
			}
		}

		formulaList->MoveNext();
	}

	//After the last token is read, pop the remainder of the stack and write any symbol (except left parenthesis) to output. 
	while (!operandStack->IsEmpty()) {
		FormulaItem* poppedOperand = operandStack->Pop();

		if (poppedOperand->FormulaType != FormulaType::Parenthesis) {
			outputStack->Push(poppedOperand);
		}
	}

	//Reverse the stack
	outputStack = outputStack->Reverse();

	return outputStack;
}