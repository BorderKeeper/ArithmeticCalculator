#pragma once

template <typename Type>
class ListItem {

public:
	Type Item;
	ListItem* Next;

	ListItem(Type item) {
		Item = item;
		Next = nullptr;
	}

	~ListItem() {	
		delete Next;
	}
};

template <typename Type>
class LinkedList {

private:
	ListItem<Type>* _start;
	ListItem<Type>* _current;
	ListItem<Type>* _end;
	int iterator;

public:
	LinkedList() {
		_start = nullptr;
		_end = nullptr;
		_current = nullptr;
		iterator = 0;
	}

	~LinkedList() {
		delete _start;
	}

	void Append(Type item) {
		ListItem<Type>* listItem = new ListItem<Type>(item);

		if (_start == nullptr) {
			_start = listItem;
			_end = listItem;
		}
		else {
			_end->Next = listItem;
			_end = listItem;
		}
	}

	void Preface(Type item) {
		ListItem<Type>* listItem = new ListItem<Type>(item);

		if (_start == nullptr) {
			_start = listItem;
			_end = listItem;
			_current = listItem;
		}
		else {
			listItem->Next = _start;
			_start = listItem;
		}
	}

	void AddAfter(Type existingItem, Type newItem) {
		ListItem listItem = new ListItem(newItem);

		if (existingItem == _end) {
			Append(newItem);
			return;
		}

		ListItem pointer = _start;
		while (pointer != nullptr) {
			if (pointer->Item == existingItem.Item) {
				listItem->Next = pointer->Next;
				pointer->Next = listItem;
				return;
			}

			pointer = pointer.Next;
		}
	}

	void RemoveLast() {
		ListItem<Type>* item = _start;
		ListItem<Type>* prevItem = _start;

		if (_start == nullptr) {
			return;
		}

		if (_start == _end) {
			_start = nullptr;
			_end = nullptr;
			_current = nullptr;
		}

		while (item->Next != nullptr) {
			prevItem = item;
			item = item->Next;
		}

		prevItem->Next = nullptr;
		_end = prevItem;
	}

	Type Get(int index) {
		iterator = 0;

		ListItem pointer = _start;
		while (pointer != nullptr) {
			if (iterator == index) {
				return pointer;
			}

			iterator++;
			pointer = pointer.Next;
		}

		return nullptr;
	}

	Type First() {
		return _start->Item;
	}

	Type Last() {
		return _end->Item;
	}

	Type GetCurrent() {
		return _current->Item;
	}

	void MoveNext() {
		_current = _current->Next;
	}

	void MoveFirst() {
		_current = _start;
	}

	bool AtEnd() {
		return _current == nullptr;
	}

	int Length() {		
		int counter = 0;
		ListItem<Type>* item = _start;

		while (item != nullptr) {
			counter++;
			item = item->Next;
		}

		return counter;
	}

	bool IsEmpty() {
		return _start == nullptr;
	}
};