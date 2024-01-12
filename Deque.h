#pragma once
template <typename T>
class Deque
{
	int GetSize() const;
	void PushFront(const T& element);
	T PopFront();
	void PushBack(const T& element);
	T PopBack();
	T PeekFront() const;
	T PeekBack() const;
};

