#pragma once

#include<string>
#include<iostream>
#include "Post.h"
using namespace std;

const int Forum_Size = 101;
typedef string ForumKeyType;
typedef Post TopicType;


class Forum
{
private:
	struct Node
	{
		ForumKeyType key;
		TopicType post;
		Node* next;
	};

	Node* items[Forum_Size];
	int  size;

public:
	Forum();
	~Forum();
	int hashForum(ForumKeyType key);
	bool addForum(ForumKeyType newKey);
	void removeForum(ForumKeyType key);
	TopicType getForum(ForumKeyType key);
	bool isEmptyForum();
	int getLengthForum();
	void printForum();
	bool addPost(string topic, string title, string description);
};
