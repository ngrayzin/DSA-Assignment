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
#include "Topic.h"
#include <iostream>
#include <string>
#include<fstream>

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

void Topic::saveToTextFile() 
{
    // Input stream class to
 // operate on files.
    ifstream ifile("topics.txt", ios::in);

    // Output stream class to
    // operate on files.
    ofstream file("topics.txt", ios::out | ios::app);

    // check if file exists
    if (!ifile.is_open()) {

        // file not found (i.e, not opened).
        // Print an error message.
        cout << "file not found";
    }
    else {
        // then add more lines to
        // the file if need be
        file << topicName << endl;
        file.close();
        cout << "Created!" << endl;
    }
}
