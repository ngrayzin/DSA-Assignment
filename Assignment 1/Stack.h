#pragma once
#include <string>
#include <iostream>
/**
* Group: 7
* -----------------------------------
* Name Member 1:         Low Hong Wei
* Student ID Member 1:   S10203927J
*
* Name Member 2:         Ng Ray Zin
* Student ID Member 2:   S10222457
* ------------------------------------
*/
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
	/**
	* Description:
	* Initalises the stack data structure
	*
	* Input:
	* None
	*
	* Output:
	* None
	*/
	Stack();

	/**
	* Description:
	* Deconstructor for the stack data structure. Deletes it when finished with the program
	*
	* Input:
	* None
	*
	* Output:
	* None
	*/
	~Stack();

	/**
	* Description:
	* Adds an item into the stack data structure through Node
	*
	* Input:
	* The item. Since this is a generic data struct it can be anything
	*
	* Output:
	* Boolean. True if it was successfully added, False if it was not.
	*/
	bool push(ItemType item);

	/**
	* Description:
	* Removes the item at the very top of the stack
	*
	* Input:
	* None
	*
	* Output:
	* Removal of the topNode
	*/
	bool pop();

	/**
	* Description:
	* Removes the item at the top of the stack but returns that item to a reference
	*
	* Input:
	* ItemType reference so that it can be returned
	*
	* Output:
	* Boolean. True if successfully removed, False if unsuccessful.
	*/
	bool pop(ItemType& item);

	/**
	* Description:
	* Checks if the stack is empty
	*
	* Input:
	* None
	*
	* Output:
	* Boolean. True if there are no Nodes that is in topNode. False if there is
	*/
	bool isEmpty();

	/**
	* Description:
	* Inverses the stack. The topNode will be at the bottom while the Node at the bottom will be at the top. The stack will be basically flipped
	*
	* Input:
	* None
	*
	* Output:
	* A flipped stack
	*/
	Stack<ItemType> inverseStack();

	/**
	* Description:
	* Clears all the Nodes from the stack
	*
	* Input:
	* Stack that user wants to clear
	*
	* Output:
	* Empty stack
	*/
	void clear(Stack<ItemType>& s);

	/**
	* Description:
	* Gets the top of the stack and returns it. It is the topNode and returns its item
	*
	* Input:
	* None
	*
	* Output:
	* Item at the top of the Stack
	*/
	ItemType top();

	/**
	* Description:
	* Gets the length of the stack
	*
	* Input:
	* None
	*
	* Output:
	* The length of the stack
	*/
	int getLength();

	/**Rayzin Help input here
	* Description:
	* 
	*
	* Input:
	* 
	*
	* Output:
	* 
	*/
	List<ItemType> toList();

	/**
	* Description:
	* Prints the contents of the stack in order of insertion
	*
	* Input:
	* Stack that user wants to print
	*
	* Output:
	* Printed Statement
	*/
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