#pragma once

#ifndef STACK_H
#define STACK_H

const int STACK_MAX = 10;

template<typename T>
class Stack
{
public:
	Stack();

	bool push(T data);
	bool pop(T& out);
	bool is_empty();

private:
	T _array[STACK_MAX];
	unsigned int top;
};

template<typename T>
inline Stack<T>::Stack()
{
	top = 0;
}

template<typename T>
inline bool Stack<T>::push(T data)
{
	if(top == STACK_MAX)
	{
		return false;
	}

	_array[top] = data;
	top++;

	return true;
}

template<typename T>
inline bool Stack<T>::pop(T& out)
{
	if(top == 0)
	{
		return false;
	}

	out = _array[top - 1];

	top--;

	return true;
}

template<typename T>
inline bool Stack<T>::is_empty()
{
	return (top == 0);
}

#endif