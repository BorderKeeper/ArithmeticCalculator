#pragma once
template <typename Type>
class List {
public:
	virtual void Append(Type item) = 0;
	virtual void Preface(Type item) = 0;
	virtual void Remove(int index) = 0;
	virtual void Remove(Type item) = 0;
	virtual Type Get(int index) = 0;
	virtual Type Start() = 0;
	virtual Type Tail() = 0;
	virtual Type GetCurrent() = 0;
	virtual void MoveNext() = 0;
	virtual void MoveFirst() = 0;
	virtual void AtEnd() = 0;
};