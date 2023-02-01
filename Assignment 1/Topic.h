#pragma once
#include <string>
#include "List.h"
#include "Post.h"
typedef Post TopicType;

class Topic {
private:
	string topicName;
	List<TopicType> postList;
public:
	Topic();//Needed
	Topic(string topicName, List<TopicType> postList);//Needed
	void setTopicName(string t);//Not Needed
	string getTopic(); //Needed
	void setPost(List<TopicType> p); //Not Needed
	List<TopicType> getPosts(); //Needed
};