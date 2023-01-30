#include "List.h"

using namespace std;


List::List() {
	size = 0;
	firstNode = NULL;
}

List::~List() {
	Node* temp = firstNode;
	while (temp != NULL)
	{
		firstNode = firstNode->next;
		temp->next = NULL;
		delete temp;
		temp = firstNode;
	}
	size = 0;
}

bool List::add(string username, string postTitle, string postContent)
{
	Node* newNode = new Node;
	newNode->username = username;
	newNode->postTitle = postTitle;
	newNode->postContent = postContent;
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

//bool List::add(int index, ItemType item)
//{
//	//if (index < size && index >= 0) {
//	//	//create the node
//	//	Node* newNode = new Node;
//	//	//store the note
//	//	newNode->item = item;
//	//	//initialize the next pointer to null
//	//	newNode->next = NULL;
//	//	//if list is empty
//	//	if (index == 0) {
//	//		newNode->next = firstNode;
//	//		//set first node (pointer) to point ot new node
//	//		firstNode = newNode;
//	//	}
//	//	else {
//	//		//traverse to last node
//	//		Node* current = firstNode;
//	//		for (int i = 0; i < index - 1;i++) {
//	//			current = current->next;
//	//		}
//	//		//set last node to point to indexed node
//	//		newNode->next = current->next;
//	//		//set that node to point to the new node
//	//		current->next = newNode;
//
//	//	}
//	//	size++;
//	//	return true;
//	//}
//	//else {
//	//	return false;
//	//}
//	return false; //removee this
//}

void List::remove(int index)
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

List List::getAllPostbyUser(string username)
{
	List list;
	Node* current = firstNode;
	for (int i = 0; i < size; i++)
	{
		if (current->username == username) {
			list.add(current->username, current->postTitle, current->postContent);
		}
		current = current->next;
	}
	return list;
}

bool List::isEmpty()
{
	return size == 0;
}

int List::getLength()
{
	return size;
}

void List::print()
{
	Node* current;
	current = firstNode;

	while (current != NULL) {
		cout << current->username << current->postTitle << current->postContent << "." << endl;
		current = current->next;
	}
}