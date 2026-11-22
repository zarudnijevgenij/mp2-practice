//#pragma once
#ifndef __TStack_H__
#define __TStack_H__
#include <iostream>
using namespace std;
//#include <algorithm>
//#include <stdexcept>

const int STACK_MAX_SIZE = 1000000000;

template <typename T>
class TStack {
private:
	int maxsize;
	int top;
	T* pMem;
public:
	TStack(int maxsize) : maxsize(maxsize) {
		if (maxsize > STACK_MAX_SIZE || maxsize <= 0) {
			throw out_of_range("incorrect stack size");
		}
		top = -1;
		pMem = new T[maxsize];
	}

	TStack(const TStack<T>& temp) {
		maxsize = temp.maxsize;
		top = temp.top;
		pMem = new T[maxsize];
		for (int i = 0; i <= top; i++) { pMem[i] = temp.pMem[i]; }
	}

	TStack(TStack<T>&& temp) : maxsize(temp.maxsize), top(temp.top), pMem(temp.pMem) {
		temp.maxsize = 0;
		temp.top = -1;
		temp.pMem = nullptr;
	}

	~TStack() {
		delete[] pMem;
	}

	TStack<T>& operator =(const TStack<T>& temp) {
		if (this == &temp) return *this;
		if (maxsize != temp.maxsize) {
			delete[] pMem;
			maxsize = temp.maxsize;
			pMem = new T[maxsize];
		}
		top = temp.top;
		for (int i = 0; i <= top; i++) { pMem[i] = temp.pMem[i];}
		return *this;
	}

	bool operator==(const TStack<T>& temp) const {
		if (maxsize != temp.maxsize) return 0;
		if (top != temp.top) return 0;
		for (int i = 0; i <= top; i++) {
			if (pMem[i] != temp.pMem[i]) return 0;
		}
		return 1;
	}

	bool operator!=(const TStack<T>& temp) const
	{
		return (!(*this == temp));
	}

	size_t size() {return top + 1;}
	bool isEmpty() const {return top == -1;}
	bool isFull() const {return top == maxsize - 1;}

	T Top() {
		if (isEmpty()) throw out_of_range("stack is empty");
		return pMem[top];
	}
	void push(const T& elem) {
		if (isFull()) throw out_of_range("stack is full");
		pMem[++top] = elem;
	}
	void pop() {
		if (isEmpty()) throw out_of_range("stack is empty");
		top--;
	}
};

#endif