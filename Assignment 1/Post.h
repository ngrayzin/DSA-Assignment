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
	Stack<string> replies;
	List<string> likeList;


public:
	Post();
	Post(string title, string description, string username, string topic, List<string> likeList);
	void setPostTitle(string title);
	string getPostTitle();
	void setDescription(string description);
	string getDescription();
	void setUser(string username);
	string getUser();
	void setTopic(string topic);
	string getTopic();
	void saveToTextFile();
	void setLikeList(List<string> likeList);
	List<string> getLikeList();
	void readTextFileByUser(User user);
	List<Post> readTextFileByTopic(string topicName);
	bool addReply(string replyMsg);
	void printReplies();

};