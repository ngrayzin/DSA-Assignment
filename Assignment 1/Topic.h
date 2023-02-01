#pragma once
#include <string>
#include "List.h"
#include "Post.h"
typedef Post PostType;

class Topic {
private:
	string topicName;
	List<PostType> postList;
public:
	Topic();//Needed
	Topic(string topicName, List<PostType> postList);//Needed
	void setTopicName(string title);//Not Needed
	string getTopic(); //Needed
	void setPost(List<PostType> postList); //Not Needed
	List<PostType> getPosts(); //Needed
	int addPost(PostType post);
};