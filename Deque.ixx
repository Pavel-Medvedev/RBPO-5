module;
#include <initializer_list>
#include <iterator>
#include <iostream>
#include "Deque.h"
export module DequeBasedOnBidirectionalCyclicLinkedList;

export namespace DequeNamespace {
	template <typename T>
	class DequeBasedOnBidirectionalCyclicLinkedList : virtual Deque<T>
	{
		using Iterator = T*;

		class CyclicLinkedList
		{
		public:
			CyclicLinkedList() : data(0), next(this) {};
			explicit CyclicLinkedList(T data = T(), CyclicLinkedList* next = nullptr)
				: data(data), next(next)
			{
				if (!this->next)
					this->next = this;
			};
			CyclicLinkedList*& Last() { 
				CyclicLinkedList* temp = this;
				while (temp->next != this)
					temp = temp->next;
				return temp; 
			};
			CyclicLinkedList* Next() { return this->next; };
			CyclicLinkedList* SetNext(CyclicLinkedList* next) { return this->next = next; };
			T& Value() { return this->data; };
			CyclicLinkedList(const CyclicLinkedList&);
			CyclicLinkedList(CyclicLinkedList&&);
			explicit CyclicLinkedList(std::initializer_list<T>);
			unsigned GetSize() const;
			void InsertAt(T value, int index)
			{
				if (!index)
					throw NULL;
				CyclicLinkedList* temp = this;
				for (auto i = 1; i < index; i++)
					temp = temp->next;
				temp->next = new CyclicLinkedList(value, temp->next);
			};
			T RemoveAt(int index)
			{
				try {
					CyclicLinkedList* temp = this;
					T data;
					for (auto i = 0; i < index - 1; i++)
						temp = temp->next;
					CyclicLinkedList* onDelete = temp->next;
					temp->next = onDelete->next;
					data = onDelete->data;
					delete onDelete;
					return data;
				}
				catch (...) {}
				return T();
			};


		private:
			T data;
			CyclicLinkedList* next;
		};
		CyclicLinkedList* list;
		unsigned size;

	public:
		DequeBasedOnBidirectionalCyclicLinkedList();
		explicit DequeBasedOnBidirectionalCyclicLinkedList(unsigned);
		DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList&);
		DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList&&);
		DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T>);
		~DequeBasedOnBidirectionalCyclicLinkedList();
		unsigned GetSize();

		Iterator begin();
		Iterator begin() const;
		Iterator end();
		Iterator end() const;
		const T& operator[](int) const;
		T& operator[](int);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(const DequeBasedOnBidirectionalCyclicLinkedList&);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(DequeBasedOnBidirectionalCyclicLinkedList&&);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T>);
		void PushFront(const T& element);
		void PushBack(const T& element);
		T PopFront();
		T PopBack();
		T PeekFront();
		T PeekBack();
	};









	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList()
		: size(0), list(nullptr){}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(unsigned size)
	{
		if (size <= 0)
			throw 0;
		list = new CyclicLinkedList(T());
		for (auto i = 1; i < size; i++)
			PushBack(0);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList& obj)
	{
		list = new CyclicLinkedList(obj.list->Value());
		CyclicLinkedList* iterator = obj.list->Next();
		while (iterator != obj.list)
		{
			PushBack(iterator->Value());
			iterator = iterator->Next();
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList&& obj)
	{
		list = obj.list;
		size = obj.size;
		obj.list = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist)
	{
		for (const auto& element : ilist)
		{
			PushBack(element);
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::~DequeBasedOnBidirectionalCyclicLinkedList()
	{
		for (auto i = 0; i < size; i++)
			PopBack();
	}

	template<typename T>
	unsigned DequeBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
	{
		return size;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::begin()
	{
		return Iterator(list);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::begin() const
	{
		return Iterator(list);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::end()
	{
		return Iterator(list->Last());
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::end() const
	{
		return Iterator(list->Last());
	}

	template<typename T>
	const T& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index) const
	{
		CyclicLinkedList* iterator = this;
		for (auto i = 0; i < index; i++)
			iterator = iterator->Next();
		return iterator->Value();
	}

	template<typename T>
	T& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index)
	{
		CyclicLinkedList* iterator = this->list;
		for (auto i = 0; i < index; i++)
			iterator = iterator->Next();
		return iterator->Value();
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(const DequeBasedOnBidirectionalCyclicLinkedList& obj)
	{
		*list = *obj.list;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(DequeBasedOnBidirectionalCyclicLinkedList&& obj)
	{
		list = obj.list;
		size = obj.size;
		obj.list = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist)
	{
		for (const auto& element : ilist)
			Push(element);
		return *this;
	}

	template<typename T>
	void DequeBasedOnBidirectionalCyclicLinkedList<T>::PushFront(const T& element)
	{
		try {
			if (!list) {
				list = new CyclicLinkedList(element);
				size++;
			}
			CyclicLinkedList* temp = list;
			list = new CyclicLinkedList(element, temp);
			temp->Last()->SetNext(list);
			size++;
		}
		catch (...) {}
	}

	template<typename T>
	void DequeBasedOnBidirectionalCyclicLinkedList<T>::PushBack(const T& element)
	{
		try {
			if (!list) {
				list = new CyclicLinkedList(element);
				size++;
				return;
			}
			list->InsertAt(element, size);
			size++;
		}
		catch (...) {}
	}

	template<typename T>
	T DequeBasedOnBidirectionalCyclicLinkedList<T>::PopFront()
	{
		try
		{
			CyclicLinkedList* temp = list;
			T value = list->Value();
			list = list->Next();
			temp->Last()->SetNext(list->Next());
			delete temp;
			--size;
			return value;
		}
		catch (...)
		{

		}
		return T();
	}

	template<typename T>
	T DequeBasedOnBidirectionalCyclicLinkedList<T>::PopBack()
	{
		try
		{
			list->RemoveAt(size - 1);
			--size;
			return list->Last()->Value();
		}
		catch (...)
		{

		}
		return T();
	}

	template<typename T>
	T DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekFront()
	{
		if (list)
			return list->Value();
		return T();
	}

	template<typename T>
	T DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekBack()
	{
		if (list)
			return list->Last()->Value();
		return T();
	}




	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(const CyclicLinkedList& obj)
	{
		const CyclicLinkedList* iterator = obj.next;
		CyclicLinkedList onDelete = this->next;
		this = new CyclicLinkedList(obj.data, this, this);
		while (iterator->next != obj)
		{
			InsertAt(iterator, -1);
			iterator = iterator->next;
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(CyclicLinkedList&& obj)
	{
		next = obj.next;
		data = obj.data;
		obj.next = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(std::initializer_list<T> ilist)
	{
		CyclicLinkedList* temp = new CyclicLinkedList(T());
		size = 1;
		for (const auto& element : ilist)
			(*temp).InsertAt(element, size++);
	}

	template<typename T>
	unsigned DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::GetSize() const
	{
		CyclicLinkedList* iterator = this->next;
		if (!this->next)
			return 0;
		unsigned count = 1;
		while (iterator != this)
			count++;
		return count;
	}
}



