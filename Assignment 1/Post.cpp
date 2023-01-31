#include "Post.h"
#include <iostream>
#include <string>
using namespace std;

Post::Post() {
	for (int i = 0; i < Post_Size; i++) {
		posts[i] = NULL;
	}
	size = 0;
}

Post::~Post() {
	for (int i = 0; i < Post_Size; i++) {
		posts[i] = NULL;
		delete posts[i];
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

int hashTopic(string k) {
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
		currentHash = currentHash % Post_Size;
	}
	return currentHash;
}

bool Post::createPost(string title, string description) {
	int index = hashTopic(title);
	Node* nNode = new Node;
	nNode->TitleKey = title;
	nNode->description = description;
	nNode->next = NULL;
	nNode->reply = NULL;
	posts[index] = nNode;
	return true;
}

void Post::printPosts() {
	for (int i = 0; i < Post_Size; i++) {
		if (posts[i] != NULL) {
			Node* current = posts[i];
			while (current != NULL) {
				cout << "Post " << i << endl << "Title: " << current->TitleKey << endl << "Description: " << current->description << endl;
				current = current->next;
			}
		}
	}
}