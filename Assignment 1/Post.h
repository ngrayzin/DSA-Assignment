#pragma once
#include <string>
#include <iostream>
#include "User.h"

class Post {
private:
	string title;
	string description;
	User user;


public:
	Post();
	Post(string title, string description, User user);
	void setPostTitle(string title);
	string getPostTitle();
	void setDescription(string description);
	string getDescription();
	void setUser(User user);
	User getUser();
};