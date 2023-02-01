#pragma once
#include<string>
#include<iostream>
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

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	// return the item in the specified index of the list
	ItemType get(int index);

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
	//Node* temp = firstNode;
	//while (temp != NULL)
	//{
	//	firstNode = firstNode->next;
	//	temp->next = NULL;
	//	delete temp;
	//	temp = firstNode;
	//}
	//size = 0;
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
ItemType List<ItemType>::get(int index)
{
	// If index is valid
	if (index < size && index >= 0) {
		// Traverse the list to the index
		Node* current = firstNode;
		for (int i = 0; i <= (index - 1); i++)
			current = current->next;

		// Return the item contained in the node
		return current->item;
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
	/*Node* current;
	current = firstNode;

	while (current != NULL) {
		cout << current->item << "." << endl;
		current = current->next;
	}*/
}

