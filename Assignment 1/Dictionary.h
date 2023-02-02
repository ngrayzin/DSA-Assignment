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

    ItemType& getAddress(KeyType key);

	bool contain(KeyType key, ItemType item);

	bool contain(KeyType key);

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

    void print();

    //List<ItemType> getAll();
	//------------------- Other useful functions -----------------

	// display the items in the Dictionary
	//void print();

	// void replace(KeyType key, ItemType item);
	// bool contains(KeyType key);
};


template <typename ItemType>
Dictionary<ItemType>::Dictionary() {
    size = 0;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        items[i] = nullptr;
    }
}

template <typename ItemType>
Dictionary<ItemType>::~Dictionary() {
    for (int i = 0; i > MAX_SIZE; i++) {
        if (items[i] != NULL) {
            Node* current = items[i];
            while (current != NULL) {
                Node* remove = current;
                current = current->next;
                remove = NULL;
                delete remove;
            }
        }
    }
}

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
    if (key.size() < 1) {
        return -1;
    }

    unsigned long int value = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        value += charvalue(key[i]) * pow(26, i);
    }

    return value % MAX_SIZE;
}

template <typename ItemType>
bool Dictionary<ItemType>::add(KeyType newKey, ItemType newItem)
{
    // Compute the index using hash function
    int hashValue = hash(newKey);

    //Get the node from the items 
    Node* node = items[hashValue];

    //Create a new node
    Node* newNode = new Node;

    //Set Items and keys into the newNode
    newNode->item = newItem;
    newNode->key = newKey;
    newNode->next = NULL;


    // Check if thee if item in the node is empty
    if (!node) {
        //Set list at index to point to new node 
        items[hashValue] = newNode;

    }
    else {
        //Check if the first node key is the smae 
        if (node->key == newNode->key) {
            return false;
        }
        else {

            //Trasverse throught the linked list
            while (node->next) {
                //Assign it to the next node to node 
                node = node->next;
                //Check if the node has the same key 
                if (node->key == newNode->key) {
                    return false;
                }
            }
        }


        //Set the next to the new node 
        node->next = newNode;
    }

    // Increase the size by 1
    size++;

    // Return true  
    return true;
}

template <typename ItemType>
void Dictionary<ItemType>::remove(KeyType key)
{
    int index = hash(key);

    Node* item = items[index];

    if (item->next == nullptr)
    {
        items[index] = nullptr;
        delete item;
        return;
    }

    while (item->next->key.compare(key) != 0 && item != nullptr)
    {
        item = item->next;
    }

    Node* tmpNodePtr = item->next;

    item->next = tmpNodePtr->next;

    delete tmpNodePtr;

    size--;
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
ItemType& Dictionary<ItemType>::getAddress(KeyType key)
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
}

template <typename ItemType>
bool Dictionary<ItemType>::contain(KeyType key, ItemType item)
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
bool Dictionary<ItemType>::contain(KeyType key)
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

//template <typename ItemType>
//List<ItemType> Dictionary<ItemType>::getAll() {
//    List<ItemType> values;
//    for (int i = 0; i < keys.getLength(); i++) {
//        values.add(items[i]);
//    }
//    return values;
//}

template <typename ItemType>
void Dictionary<ItemType>::print() {
    int count = 1;
    if (size > 0) {
        for (int i = 0; i < MAX_SIZE; i++) {
            if (items[i] != NULL) {
                cout << "[" << count << "] " << items[i]->key << endl;
                count++;
            }
        }
    }
    else {
        cout << "no content" << endl;
    }
}


