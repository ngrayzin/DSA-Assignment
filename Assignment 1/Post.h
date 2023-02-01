#pragma once
#include <string>
#include <iostream>
#include "User.h"

class Post {
private:
	string topic;
	string title;
	string description;
	User user;
	int likes;


public:
	Post();
	Post(string title, string description, User user, string topic);
	void setPostTitle(string title);
	string getPostTitle();
	void setDescription(string description);
	string getDescription();
	void setUser(User user);
	User getUser();
	void setTopic(string topic);
	string getTopic();
};