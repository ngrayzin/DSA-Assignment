#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "List.h"
using namespace std;

template <typename ItemType>
class Stack {
private:
	struct Node
	{
		ItemType item;   // to store data
		Node* next;  // to point to next node
	};

	Node* topNode;

public:
	Stack();
	~Stack();
	bool push(ItemType item);
	bool pop();
	bool pop(ItemType& item);
	bool isEmpty();
	Stack<ItemType> inverseStack();
	void clear(Stack<ItemType>& s);
	ItemType top();
	int getLength();
	List<ItemType> toList();
	void printInversed(Stack<ItemType> s);
};

template <typename ItemType>
Stack<ItemType>::Stack() {
	topNode = NULL;
}

template <typename ItemType>
Stack<ItemType>::~Stack() {
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


template <typename ItemType>
bool Stack<ItemType>::push(ItemType item) {
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

template <typename ItemType>
bool Stack<ItemType>::pop() {
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

template <typename ItemType>
bool Stack<ItemType>::pop(ItemType& item) {
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

template <typename ItemType>
bool Stack<ItemType>::isEmpty() {
	if (topNode == NULL) {return true;}
	else { return false; }
}

template <class StackType> Stack<StackType> Stack<StackType>::inverseStack() {
	Stack nStack;
	Node* current = topNode;
	while (current != NULL) {
		nStack.push(current->item);
		current = current->next;
	}
	return nStack;
}


template <typename ItemType>
void Stack<ItemType>::clear(Stack<ItemType>& s) {
	while (s.topNode)
	{
		Node* remove = s.topNode;
		s.topNode = s.topNode->next;
		remove = NULL;
		delete remove;
	}
}

template <typename ItemType>
int Stack<ItemType>::getLength() {
	int count = 0;
	Node* curr = topNode;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

template <typename ItemType>
ItemType Stack<ItemType>::top() {
	return topNode->item;
}


template <typename ItemType>
List<ItemType> Stack<ItemType>::toList() {
	List<ItemType> list = List<ItemType>();
	Node* curr = topNode;
	while(curr != NULL) {
		list.add(curr->item);
		curr = curr->next;
	}
	return list;
}

template <typename ItemType> void Stack<ItemType>::printInversed(Stack<ItemType> s) {
	s = s.inverseStack();
	Node* current = s.topNode;
	while (current) {
		cout << current->item;
		current =current->next;
	}
}