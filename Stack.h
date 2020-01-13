#pragma once

#include "LinkedList.h"
#include <string>

template <typename Type>
class Stack {
private:
	LinkedList<Type>* _list;

public:
	Stack() {
		_list = new LinkedList<Type>();
	}

	void Push(Type item) {
		_list->Append(item);
	}

	Type Pop() {
		Type last = _list->Last();
		_list->RemoveLast();
		return last;
	}

	Type Peek() {
		return _list->Last();
	}

	bool IsEmpty() {
		return _list->IsEmpty();
	}

	Stack<Type>* Reverse() {
		Stack<Type>* reversedStack = new Stack<Type>();

		while(!IsEmpty()) {
			reversedStack->Push(Pop());
		}
		
		return reversedStack;
	}
};