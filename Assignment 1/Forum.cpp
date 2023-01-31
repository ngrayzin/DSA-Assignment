#include "Forum.h"
#include <string>
#include <iostream>
using namespace std;

Forum::Forum() {
	for (int i = 0; i < Forum_Size; i++) {
		items[i] = NULL;
	}
	size = 0;
}

Forum::~Forum() {
	for (int i = 0; i < Forum_Size; i++) {
		items[i] = NULL;
		delete items[i];
	}
	size = 0;
}

int alphaIndex(char s) {
	if (isalpha(s))
	{
		if (isupper(s))
			return (int)s - (int)'A';
		else
			return (int)s - (int)'a' + 26;
	}
	else
		return -1;
}

int Forum::hashForum(ForumKeyType k) {
	int currentHash = 0;
	if (k.empty() == false) {
		currentHash = alphaIndex(k[0]);
	}
	else {
		return -1;
	}
	for (int i = 1; i < k.size(); i++) {
		currentHash = currentHash * 52;
		currentHash = currentHash + alphaIndex(k[i]);
		currentHash = currentHash % Forum_Size;
	}
	return currentHash;
}

bool Forum::addForum(ForumKeyType TopicKey) {
	int index = hashForum(TopicKey);
	Node* nNode = new Node;
	nNode->key = TopicKey;
	nNode->next = NULL;
	if (index != -1) {
		if (items[index] == NULL) {
			items[index] = nNode;
			return true;
		}
		else {
			if (items[index]->key == TopicKey)
				return false;
			Node* current = items[index];
			while (current->next != NULL) {
				if (current->key == TopicKey) {
					return false;
				}
				current = current->next;
			}
			current->next = nNode;
			return true;
		}
	}
	return false;
}

void Forum::removeForum(ForumKeyType k) {
	int index = hashForum(k);
	if (items[index]->key == k) {
		if (items[index]->next != NULL) {
			Node* remove = items[index];
			items[index] = items[index]->next;
			delete remove;
		}
		else {
			items[index] = NULL;
		}
	}
	else {
		Node* current = items[index];
		Node* remove;
		while (current != NULL) {
			if (current->next->key == k) {
				remove = current->next;
				if (current->next->next != NULL) {
					current->next = current->next->next;
				}
				else {
					current->next = NULL;
				}
				delete remove;
			}
			current = current->next;
		}
	}
}

bool Forum::addPost(string topic, string title, string description) {
	int index = hashForum(topic);
	Node* current = items[index];
	Post p;
	p.createPost(title, description);
	while (current != NULL) {
		if (current->key == topic) {
			current->post = p;
			cout << "Doneddd" << endl;
		}
	}
	return true;
}


//void Forum::printForum() {
//	for (int i = 0; i < Forum_Size; i++) {
//		if (items[i] != NULL) {
//			if (items[i]->next == NULL) {
//				cout << "Topic: " << items[i]->key << endl <<"Reason: " << items[i]->topic. << endl;
//			}
//			else {
//				Node* current = items[i];
//				while (current != NULL) {
//					cout << "Topic: " << current->key << endl << "Reason: " << current->item << endl;
//					current = current->next;
//				}
//			}
//		}
//	}
//}