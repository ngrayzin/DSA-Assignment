#include "Post.h"
#include <string>
#include <iostream>
using namespace std;

Post::Post()
{
}

Post::Post(string t, string d, User u) {
	title = t;
	description = d;
	user = u;
}

void Post::setPostTitle(string t) {
	title = t;
}

string Post::getPostTitle() {
	return title;
}

void Post::setDescription(string d) {
	description = d;
}

string Post::getDescription() {
	return description;
}

void Post::setUser(User u) {
	user = u;
}

User Post::getUser() {
	return user;
}