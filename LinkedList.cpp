#include "IList.h"

template <typename Type>
class LinkedList : public ILinkedList {
	public:
		LinkedList() {
			_start = null;
			_end = null;
			_current = null;
			index = 0;
		}

		void Append(Type item) {
			ListItem listItem = new ListItem(item);

			if (_start == null) {
				_start = listItem;
				_end = listItem;
			}
			else {
				_end.Next = listItem;
				_end = listItem;
			}
		}

		void Preface(Type item) {
			ListItem listItem = new ListItem(item);

			if (_start == null) {
				_start = listItem;
				_end = listItem;
				_current = listItem;
			}
			else {
				listItem.Next = _start;
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
			while (pointer != null) {
				if (pointer.Item == existingItem.Item) {
					listItem.Next = pointer.Next;
					pointer.Next = listItem;
					return;
				}

				pointer = pointer.Next;
			}			
		}

		void Remove(Type item) {
			ListItem pointer = _start;

			if (item == _start) {
				_start = _start.Next;
			}

			while (pointer != null) {
				if (pointer.Next == item) {
					pointer.Next = pointer.Next.Next;
					return;
				}

				pointer = pointer.Next;
			}
		}

		Type Get(int index) {
			iterator = 0;

			ListItem pointer = _start;
			while (pointer != null) {
				if (iterator == index) {
					return pointer;
				}

				iterator++;
				pointer = pointer.Next;
			}

			return null;
		}
		Type Start(){
			return _start;
		}
		Type Tail() {
			return _end;
		}
		Type GetCurrent() {
			return _current.Item;
		}
		void MoveNext() {
			_current = _current.Next;
		}
		void MoveFirst() {
			_current = _start;
		}
		bool AtEnd() {
			return _current == _end;
		}

	private:
		ListItem _start;
		ListItem _current;
		ListItem _end;
		int iterator;
};

template <typename Type>
class ListItem {
	public:
		Type Item;
		ListItem Next;

		ListItem(Type item) {
			Item = item;
			Next = null;
		}
};