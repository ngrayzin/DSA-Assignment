#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

template <typename ItemType>
class List
{
private:
	struct Node
	{
		ItemType item;
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;			// number of items in the list

public:
	List();	// constructor

	~List();		// destructor

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(ItemType item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index <= size
	// post: item is added to the specified position in the list
	//       items after the position are shifted back by 1 position
	//       size of list is increased by 1
	bool add(int index, ItemType item); // this will prob be add the stack into the node

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       items after the position are shifted forward by 1 position
	//       size of list is decreased by 1
	void remove(int index);

	// remove an item via the itemtype
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       items after the position are shifted forward by 1 position
	//       size of list is decreased by 1
	bool remove(ItemType item);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	// return the item in the specified index of the list
	ItemType get(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	// return the item in the specified index of the list
	ItemType* getAddress(int index);

	// See if this item is in the list
	// pre : none
	// post: none
	// return true if the item is in the list; otherwise returns false
	bool contain(ItemType item);

	// See if this item is in the list and return the item
	// pre : 0 <= index < size
	// post: none
	// return the item if the item is in the list; otherwise returns noting
	ItemType search(ItemType item);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	ItemType* getPost(string userName, string title);

	//------------------- Other useful functions -----------------

	// display the items in the list
	void print();

	// void replace(int index, ItemType item);
	// int search(ItemType item);
};

template <typename ItemType>
List<ItemType>::List() {
	size = 0;
	firstNode = NULL;
}

template <typename ItemType>
List<ItemType>::~List() {
	while (firstNode != NULL) {
		Node* remove;
		if (firstNode->next != NULL) {
			remove = firstNode;
			firstNode = firstNode->next;
			remove = NULL;
			delete remove;
		}
		else {
			firstNode = NULL;
		}
	}
}

template <typename ItemType>
bool List<ItemType>::add(ItemType item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (size == 0) {
		firstNode = newNode;
	}
	else {
		Node* current = firstNode;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	size++;
	return true;
}


template <typename ItemType>
bool List<ItemType>::add(int index, ItemType item)
{
	if (index < size && index >= 0) {
		//create the node
		Node* newNode = new Node;
		//store the note
		newNode->item = item;
		//initialize the next pointer to null
		newNode->next = NULL;
		//if list is empty
		if (index == 0) {
			newNode->next = firstNode;
			//set first node (pointer) to point ot new node
			firstNode = newNode;
		}
		else {
			//traverse to last node
			Node* current = firstNode;
			for (int i = 0; i < index - 1;i++) {
				current = current->next;
			}
			//set last node to point to indexed node
			newNode->next = current->next;
			//set that node to point to the new node
			current->next = newNode;
		}
		size++;
		return true;
	}
	else {
		return false;
	}
}

template <typename ItemType>
void List<ItemType>::remove(int index)
{
	//if node is valid
	if (index < size && index >= 0) {
		//if node to be remove is fist node
		if (index == 0) {
			//set first node to point to the second node(or NULL)
			firstNode = firstNode->next;
		}
		else {
			Node* current = firstNode;
			for (int i = 0;i < index - 1;i++) {
				current = current->next;
			}
			current->next = current->next->next;
		}
		size--;
	}
}

template <typename ItemType>
bool List<ItemType>::remove(ItemType item)
{
	Node* current = firstNode;
	Node* prev = firstNode;
	if (firstNode->item == item) {
		if (firstNode->next != NULL) {
			firstNode = firstNode->next;
			size--;
			return true;
		}
		else {
			firstNode = NULL;
			size--;
			return true;
		}
	}
	else {
		while (current != NULL) {
			prev = current;
			current = current->next;
			if (current->item == item) {
				if (current->next != NULL) {
					prev->next = current->next;
					current = NULL;
					delete current;
					size--;
					return true;
				}
				else {
					prev->next = NULL;
					current = NULL;
					delete current;
					size--;
					return true;
				}
			}

		}
	}
	return false;
}

template <typename ItemType>
ItemType List<ItemType>::get(int index)
{
	// If index is valid
	if (index <= size && index >= 0) {
		// Traverse the list to the index
		Node* current = firstNode;
		for (int i = 0; i <= (index - 1); i++)
			if (current->next != NULL) {
				current = current->next;
			}

		// Return the item contained in the node
		return current->item;
	}

	return ItemType();
}

template<typename ItemType>
ItemType* List<ItemType>::getAddress(int index)
{
	// If index is valid
	if (index <= size && index >= 0) {
		// Traverse the list to the index
		Node* current = firstNode;
		for (int i = 0; i <= (index - 1); i++)
			if (current->next != NULL) {
				current = current->next;
			}

		// Return the item contained in the node
		return &current->item;
	}
	return nullptr;
}


template<typename ItemType>
bool List<ItemType>::contain(ItemType item)
{
	Node* current = firstNode;
	for (int i = 0; i <= size-1; i++) {
		if (current->item == item) {
			return true;
		}
		if (current->next != NULL) {
			current = current->next;
		}
	}
	return false;
}

template<typename ItemType>
ItemType List<ItemType>::search(ItemType item)
{
	Node* current = firstNode;
	for (int i = 0; i <= size - 1; i++) {
		if (current->item == item) {
			return current->item;
		}
		if (current->next != NULL) {
			current = current->next;
		}
	}
	return ItemType();
}

template <typename ItemType>
bool List<ItemType>::isEmpty()
{
	return size == 0;
}


template <typename ItemType>
int List<ItemType>::getLength()
{
	return size;
}

template <typename ItemType>
void List<ItemType>::print()
{
    Node *current = firstNode;
    while (current != nullptr)
    {
        cout << current->item << endl;
        current = current->next;
    }
}

template<typename ItemType>
ItemType* List<ItemType>::getPost(string userName, string title) {
	Node* current = firstNode;
	while (current != NULL) {
		if (current->item.getUser() == userName && current->item.getPostTitle() == title) {
			return &(current->item);
		}
		current = current->next;
	}
}