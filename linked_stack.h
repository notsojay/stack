// who: Jiahao Liang, Jianwen Qi
// why: lab_5
// when: 10-31-2021

#pragma once
#ifndef _LINKED_STACK_H_
#define _LINKED_STACK_H_

#include <cstddef>
#include <stdexcept>
#include <iostream>

template<class T> class LinkedStack;

/**
*	class of Node
*/
template<class T>
class Node
{
public:
	friend class LinkedStack<T>;
	
private:
	T data;
	Node* next;
	Node();
	Node(const T &data, Node<T> *next = nullptr);
};

template<class T>
Node<T>::Node():next(nullptr){}

template<class T>
Node<T>::Node(const T &data, Node<T> *next):data(data), next(next){}

/**
*	class of LinkeStack
*/
template<class T>
class LinkedStack
{
public:
	LinkedStack();
	LinkedStack(const LinkedStack&);
	~LinkedStack();
	inline bool isEmpty() const noexcept;
	inline T peek() const;
	size_t size() const;
	inline void push(const T &);
	inline void pop();
	void clear();
	void reverse();
	LinkedStack<T>& operator=(const LinkedStack<T>&);
	bool operator==(const LinkedStack<T>&) const;
	bool operator!=(const LinkedStack<T>&) const;
	friend std::ostream &operator<<(std::ostream &out, const LinkedStack &other)
	{
		if(other.isEmpty())
		{
			throw std::overflow_error("ERROR: EMPTY LINKED STACK");
		}
		Node<T>* current = other.head->next;
		while(current != nullptr)
		{
			out << current->data << " ";
			current = current->next;
		}
		return out;
	}
	
private:
	Node<T>* head;
};

template<class T>
LinkedStack<T>::LinkedStack():head(new Node<T>()){}

template<class T>
LinkedStack<T>::LinkedStack(const LinkedStack &other):head(new Node<T>())
{
	if(other.isEmpty())
	{
		return;
	}
	Node<T>* current = other.head->next;
	while(current != nullptr)
	{
		push(current->data);
		current = current->next;
	}
	reverse();
}

template<class T>
LinkedStack<T>::~LinkedStack()
{
	clear();
	delete head;
	head = nullptr;
}

template<class T>
inline bool LinkedStack<T>::isEmpty() const noexcept
{
	return head->next == nullptr ? true : false;
}

template<class T>
inline T LinkedStack<T>::peek() const
{
	if(isEmpty())
	{
		return -1;
	}
	return head->next->data;
}

template<class T>
size_t LinkedStack<T>::size() const
{
	if(isEmpty())
	{
		return 0;
	}
	Node<T> *current = head->next;
	size_t count = 0;
	while(current != nullptr)
	{
		current = current->next;
		count++;
	}
	return count;
}

template<class T>
inline void LinkedStack<T>::push(const T &data)
{
	Node<T>* top = new Node<T>(data);
	top->next = head->next;
	head->next = top;
}

template<class T>
inline void LinkedStack<T>::pop()
{
	if(isEmpty())
	{
		throw std::overflow_error("ERROR: EMPTY LINKED STACK");
	}
	Node<T>* current = head->next;
	head->next = current->next;
	delete current; current = nullptr;
}

template<class T>
void LinkedStack<T>::clear()
{
	if(isEmpty())
	{
		return;
	}
	Node<T>* current = nullptr;
	while(head->next != nullptr)
	{
		current = head->next;
		delete head;
		head = current;
	}
}

template<class T>
void LinkedStack<T>::reverse()
{
	if(isEmpty())
	{
		return;
	}
	Node<T> *previous = nullptr;
	Node<T> *current = head->next;
	Node<T> *next;
	while(current != nullptr)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	head->next = previous;
}

template<class T>
bool LinkedStack<T>::operator==(const LinkedStack<T>& other) const
{
	if(isEmpty() && other.isEmpty())
	{
		return true;
	}
	else if(size() != other.size())
	{
		return false;
	}
	Node<T> *current = head->next;
	Node<T> *duplicatedCurrent = other.head->next;
	while(current != nullptr && duplicatedCurrent != nullptr)
	{
		if(current->data != duplicatedCurrent->data)
		{
			return false;
		}
		current = current->next;
		duplicatedCurrent = duplicatedCurrent->next;
	}
	return true;
}

template<class T>
bool LinkedStack<T>::operator!=(const LinkedStack<T>& other) const
{
	if(isEmpty() && other.isEmpty())
	{
		return false;
	}
	else if(size() != other.size())
	{
		return true;
	}
	Node<T> *current = head->next;
	Node<T> *duplicatedCurrent = other.head->next;
	while(current != nullptr && duplicatedCurrent != nullptr)
	{
		if(current->data == duplicatedCurrent->data)
		{
			current = current->next;
			duplicatedCurrent = duplicatedCurrent->next;
		}
	}
	if(current == nullptr && duplicatedCurrent == nullptr)
	{
		return false;
	}
	return true;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other)
{
	if(other.isEmpty())
	{
		clear();
		return *this;
	}
	if(this == &other)
	{
		return *this;
	}
	if(!isEmpty())
	{
		clear();
		head = new Node<T>();
	}
	Node<T>* current = other.head->next;
	while(current != nullptr)
	{
		pushBack(current->data);
		current = current->next;
	}
	return *this;
}



#endif