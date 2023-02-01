#include "Topic.h"
#include <iostream>
#include <string>
using namespace std;

Topic::Topic()
{
}

Topic::Topic(string tn, List<PostType> pl) {
	topicName = tn;
	postList = pl;
}

void Topic::setTopicName(string tn) {
	topicName = tn;
}

string Topic::getTopic() {
	return topicName;
}

void Topic::setPost(List<PostType> pl) {
	postList = pl;
}

List<PostType> Topic::getPosts() {
	return postList;
}

int Topic::addPost(PostType post) {
	postList.add(post);
	return postList.getLength();
}