#include "Dictionary.h"
Dictionary::Dictionary()
{
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = NULL;
    }
}

Dictionary::~Dictionary()
{
    //for (int i = 0; i < MAX_SIZE; i++) {
    //    Node* node = items[i];
    //    if (node) {
    //        while (node->next != NULL) {
    //            Node* temp = node->next;
    //            node->next = NULL;
    //            node = node->next;
    //            delete temp;
    //        }
    //    }
    //    items[i] = NULL;
    //    delete node;
    //}
    //size = 0;
}

int charvalue(char c)
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


int Dictionary::hash(KeyType key)
{
    int total = charvalue(key[0]);
    for (int i = 1; i < key.length(); i++)
    {
        if (charvalue(key[i]) < 0)  // not an alphabet
            continue;
        total = total * 52 + charvalue(key[i]);
        total %= MAX_SIZE;
    }
    return total;
}

bool Dictionary::add(KeyType newKey, ItemType newItem)
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

void Dictionary::remove(KeyType key)
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

ItemType Dictionary::get(KeyType key)
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

bool Dictionary::returnLogin(KeyType key, ItemType item)
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

bool Dictionary::validateLogin(KeyType key)
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

bool Dictionary::isEmpty()
{
    return size == 0;
}

int Dictionary::getLength()
{
    return size;
}

void Dictionary::print()
{
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* node = items[i];
        if (node) {
            cout << node->key << " :" << node->item << endl;
            while (node->next != NULL) {
                cout << node->next->key << " :" << node->next->item << endl;
                node = node->next;
            }
        }
    }
}
