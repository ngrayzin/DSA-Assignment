#pragma once
#include <string>
#include <iostream>
#include "User.h"
#include <sstream>
#include<fstream>
#include "Stack.h"

class Post {
private:
	string topic;
	string title;
	string description;
	string username;
	//Stack<string> replies;
	int likes = 0;


public:
	Post();
	Post(string title, string description, string username, string topic);
	void setPostTitle(string title);
	string getPostTitle();
	void setDescription(string description);
	string getDescription();
	void setUser(string username);
	string getUser();
	void setTopic(string topic);
	string getTopic();
	void saveToTextFile();
	void readTextFileByUser(User user);
	List<Post> readTextFileByTopic(string topicName);
};