#pragma once
#include <string>
#include <iostream>
#include "User.h"
#include <sstream>
#include<fstream>
#include "Stack.h"
#include "Reply.h"

class Post {
private:
	string topic;
	string title;
	string description;
	string username;
	Stack<Reply> replies;
	List<string> likeList;


public:
	Post();
	Post(string title, string description, string username, string topic, List<string> likeList, Stack<Reply> replies);
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
	void addLikes(string name);
	List<string> *getLikeList();
	void readTextFileByUser(User user);
	List<Post> readTextFileByTopic(string topicName);
	void addReply(string replyMsg);
	void setReplies(Stack<Reply> replyStack);
	void printReplies();
	void printReplies(int count,Stack<Reply> replyList);
	Stack<Reply> *getReplies();
	List<Post> returnPostListByUser(User user);
	bool operator==(const Post& rhs);
	void updateTextFile(Post p);
	vector<string> split(const string& s, char delim);
	string toString();
};