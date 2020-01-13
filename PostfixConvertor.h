#pragma once

#include "LinkedList.h"
#include "FormulaItem.h"
#include "Stack.h"

class PostfixConvertor {
public:
	Stack<FormulaItem*>* CreatePostfixStack(LinkedList<FormulaItem*>* formulaList);
};