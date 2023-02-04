#pragma once
#include <string>
#include <iostream>
using namespace std;

template <class StackType> class Stack {
private:
	struct Node
	{
		StackType item;   // to store data
		Node* next;  // to point to next node
	};

	Node* topNode;

public:
	Stack();
	~Stack();
	bool push(StackType item);
	bool pop();
	bool pop(StackType& item);
	bool isEmpty();
	Stack<StackType> inverseStack();
	void clear(Stack& s);
	StackType top();
	int getLength();
};

template <class StackType> Stack<StackType>::Stack() {
	topNode = NULL;
}

template <class StackType> Stack<StackType>::~Stack() {
	Node* current = topNode;
	if (current != NULL) {
		while (current->next != NULL) {
			Node* remove = current;
			current = current->next;
			remove = NULL;
			delete remove;
		}
		current = NULL;
	}
}

template <class StackType> bool Stack<StackType>::push(StackType item) {
	Node* nNode = new Node;
	nNode->item = item;
	nNode->next = NULL;
	if (topNode == NULL) {
		topNode = nNode;
		return true;
	}
	else {
		Node* currentTop = topNode;
		nNode->next = currentTop;
		topNode = nNode;
		return true;
	}
}

template <class StackType> bool Stack<StackType>::pop() {
	if (topNode != NULL) {
		if (topNode->next != NULL) {
			Node* nextTop = topNode->next;
			topNode = nextTop;
			return true;
		}
		else {
			topNode = NULL;
			return true;
		}
	}
	return false;
}

template <class StackType> bool Stack<StackType>::pop(StackType& item) {
	if (topNode != NULL) {
		if (topNode->next != NULL) {
			item = topNode->item;
			Node* nextTop = topNode->next;
			topNode = nextTop;
			return true;
		}
		else {
			item = topNode->item;
			topNode = NULL;
			return true;
		}
	}
	return false;
}

template <class StackType> bool Stack<StackType>::isEmpty() {
	if (topNode == NULL) {return true;}
	else { return false; }
}

template <class StackType> Stack<StackType> Stack<StackType>::inverseStack() {
	Stack nStack;
	Node* current = topNode;
	while (current != NULL) {
		nStack.push(current->item);
		current =current->next;
	}
	return nStack;
}

template <class StackType> void Stack<StackType>::clear(Stack<StackType>& s) {
	while (s.topNode)
	{
		Node* remove = s.topNode;
		s.topNode = s.topNode->next;
		remove = NULL;
		delete remove;
	}
}

template <class StackType> int Stack<StackType>::getLength() {
	int count = 0;
	Node* curr = topNode;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

template <class StackType> StackType Stack<StackType>::top() {
	return topNode->item;
}