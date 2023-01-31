#pragma once
#include <iostream>
#include <string>
typedef std::string TitleType;
typedef std::string DescriptionType;
const int Post_Size = 101;

class Post
{
public:
	Post();
	~Post();
	bool createPost(std::string title, std::string description);
	bool editPost();
	bool deletePost();
	void printPosts();

private:
	struct Node
	{
		TitleType TitleKey;
		DescriptionType description;
		Node* reply;
		Node* next;
	};

	Node* posts[Post_Size];
	int  size;
};