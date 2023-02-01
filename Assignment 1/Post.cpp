#include "Post.h"
#include <string>
#include <iostream>
#include "Topic.h"
using namespace std;

Post::Post()
{
}

Post::Post(string t, string d, User u, string top) {
	title = t;
	description = d;
	user = u;
	topic = top;
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

void Post::setTopic(string t)
{
	topic = t;
}

string Post::getTopic()
{
	return topic;
}
