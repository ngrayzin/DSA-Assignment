/**
* Group: 7
* -----------------------------------
* Name Member 1:         Low Hong Wei
* Student ID Member 1:   S10203927J
*
* Name Member 2:         Ng Ray Zin
* Student ID Member 2:   S10222457
* ------------------------------------
*/
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

	/**
	* Description: 
	* Initalises the Topic class
	*/
	Topic();//Not needed

	/**
	* Description:
	* Overloaded initalise Topic class function
	*
	* Input:
	* Name of the topic
	* A list of Posts inside a linked list
	*/
	Topic(string topicName, List<PostType> postList);//Not needed

	/**
	* Description:
	* Sets a new name for the topic
	*
	* Input:
	* The new title
	*
	* Output:
	* None
	*/
	void setTopicName(string title);//Not Needed

	/**
	* Description:
	* Gets the topic title from the topic class
	*
	* Input:
	* None
	*
	* Output:
	* The topic title
	*/
	string getTopic(); //Not Needed

	/**
	* Description:
	* Sets a new list of post for the topic
	*
	* Input:
	* The new list of posts
	*
	* Output:
	* None
	*/
	void setPost(List<PostType> postList); //Not Needed

	/**
	* Description:
	* Gets the topic's list of post which contains all posts under that topic
	*
	* Input:
	* None
	*
	* Output:
	* Topic's List of posts
	*/
	List<PostType> getPosts(); //Not needed

	/**
	* Description:
	* Adds a new post into the topic's post list
	*
	* Input:
	* The new post object
	*
	* Output:
	* New length of the list
	*/
	int addPost(PostType post);

	/**Rayzin Help input here
	* Description:
	* 
	*
	* Input:
	* 
	*
	* Output:
	* 
	*/
	void saveToTextFile();
};