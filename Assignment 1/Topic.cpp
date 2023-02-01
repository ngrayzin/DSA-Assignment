#include "Topic.h"
#include <iostream>
#include <string>
using namespace std;

Topic::Topic(string tn, List<TopicType> pl) {
	topicName = tn;
	postList = pl;
}

void Topic::setTopicName(string tn) {
	topicName = tn;
}

string Topic::getTopic() {
	return topicName;
}

void Topic::setPost(List<TopicType> pl) {
	postList = pl;
}

List<TopicType> Topic::getPosts() {
	return postList;
}