#pragma once

#include <string>
#include <iostream>
#include "List.h"
#include <random>
using namespace std;

const int MAX_SIZE = 101;
typedef string KeyType;

template <typename ItemType>
class Dictionary
{
private:
	struct Node
	{
		KeyType	 key;   // search key
		ItemType item;	// data item
		Node* next;	// pointer pointing to next item with same search key
	};

	Node* items[MAX_SIZE];
	int  size; // number of items in the Dictionary
	 
public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

    int charvalue(char c);

	// add a new item with the specified key to the Dictionary
	// pre : none
	// post: new item is added to the Dictionary
	//       size of Dictionary is increased by 1
	bool add(KeyType newKey, ItemType newItem);

	// remove an item with the specified key in the Dictionary
	// pre : key must exist in the Dictionary
	// post: item is removed from the Dictionary
	//       size of Dictionary is decreased by 1
	void remove(KeyType key);


	// get an item with the specified key in the Dictionary (retrieve)
	// pre : key must exist in the dictionary
	// post: none
	// return the item with the specified key from the Dictionary
	ItemType get(KeyType key);

	bool returnLogin(KeyType key, ItemType item);

	bool validateLogin(KeyType key);

	// check if the Dictionary is empty
	// pre : none
	// post: none
	// return true if the Dictionary is empty; otherwise returns false
	bool isEmpty();

	// check the size of the Dictionary
	// pre : none
	// post: none
	// return the number of items in the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the Dictionary
	void print();

	void print1();

	// void replace(KeyType key, ItemType item);
	// bool contains(KeyType key);
};


template <typename ItemType>
Dictionary<ItemType>::Dictionary() {
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = NULL;
    }
}

template <typename ItemType>
Dictionary<ItemType>::~Dictionary() {}

template <typename ItemType>
int Dictionary<ItemType>::charvalue(char c)
{
    if (isalpha(c))
    {
        if (isupper(c))
            return (int)c - (int)'A';
        else
            return (int)c - (int)'a' + 26;
    }
    else
        return -1;
}

template <typename ItemType>
int Dictionary<ItemType>::hash(KeyType key)
{
    //int total = charvalue(key[0]);
    //for (int i = 1; i < key.length(); i++)
    //{
    //    if (charvalue(key[i]) < 0)  // not an alphabet
    //        continue;
    //    total = total * 52 + charvalue(key[i]);
    //    total %= MAX_SIZE;
    //}
    //return total;
    unsigned long hash = 5381;
    int c;

    int range = key.length() - 1;
    int num = rand() % range;
    char* abs = &key[num];

    while (c = *abs++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % MAX_SIZE;
}

template <typename ItemType>
bool Dictionary<ItemType>::add(KeyType newKey, ItemType newItem)
{
    int index = hash(newKey);
    if (items[index] == NULL) {
        Node* newNode = new Node;
        newNode->item = newItem;
        newNode->key = newKey;
        newNode->next = NULL;
        items[index] = newNode;
    }
    else {
        Node* current = items[index];
        if (current->key == newKey) {
            cout << newKey << " already exists" << endl;
            return false;
        }
        while (current->next != NULL) {
            current = current->next;
            if (current->key == newKey) {
                cout << newKey << " already exists" << endl;
                return false;
            }
        }
        Node* newNode = new Node;
        newNode->item = newItem;
        newNode->key = newKey;
        newNode->next = NULL;
        current->next = newNode;
    }
    size++;
    return true;
}

template <typename ItemType>
void Dictionary<ItemType>::remove(KeyType key)
{
    int index = hash(key);
    if (items[index] != NULL) {
        Node* current = items[index];
        if (current->key == key) {
            Node* next = current->next;
            current->next = NULL;
            Node* temp = current;
            current = next;
            items[index] = current;
            delete temp;
        }
        else {
            while (current->next != NULL) {
                current = current->next;
                if (current->key == key) {
                    Node* temp = current->next;
                    current->next = NULL;
                    current = NULL;
                    current = temp;

                }
            }
        }
        size--;
    }
}

template <typename ItemType>
ItemType Dictionary<ItemType>::get(KeyType key)
{
    int index = hash(key);
    if (items[index] != NULL) {
        Node* current = items[index];
        while (current != NULL) {
            if (current->key == key) {
                return current->item;
            }
            current = current->next;
        }
    }
    return ItemType();
}

template <typename ItemType>
bool Dictionary<ItemType>::returnLogin(KeyType key, ItemType item)
{
    int index = hash(key);
    if (items[index] != NULL) {
        Node* current = items[index];
        while (current != NULL) {
            if (current->key == key && current->item == item) {
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

template <typename ItemType>
bool Dictionary<ItemType>::validateLogin(KeyType key)
{
    int index = hash(key);
    if (items[index] != NULL) {
        Node* current = items[index];
        while (current != NULL) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

template <typename ItemType>
bool Dictionary<ItemType>::isEmpty()
{
    return size == 0;
}

template <typename ItemType>
int Dictionary<ItemType>::getLength()
{
    return size;
}

template <typename ItemType>
void Dictionary<ItemType>::print()
{
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* node = items[i];
        if (node) {
            //if (typeid(node->item).name() == "class List") {
                cout << node->key << " :" << endl;
                //node->next->item.print();
                while (node->next != NULL) {
                    cout << node->next->key << " :" << node->next->item << endl;
                    
                    node = node->next;
                }
            //}

        }
    }
}


template <typename ItemType>
void Dictionary<ItemType>::print1()
{
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = new Node;
        current = items[i];
        if (current != NULL) {
            cout << current->key << endl;
            current->item.print();
            while (current->next != NULL) {
                current = current->next;
            }
        }
    }
}

