#include "Post.h"
#include <string>
#include <iostream>
#include "Topic.h"
#include "User.h"
#include <sstream>
#include<fstream>
#include <iomanip>
#include "Stack.h"
#include "Reply.h"

using namespace std;

Post::Post()
{
}

Post::Post(string t, string d, string un, string top, List<string> list, Stack<Reply> stack) {
	title = t;
	description = d;
	username = un;
	topic = top;
    likeList = list;
    replies = stack;
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

void Post::setUser(string un) {
	username = un;
}

string Post::getUser() {
	return username;
}

void Post::setTopic(string t)
{
	topic = t;
}

string Post::getTopic()
{
	return topic;
}

void Post::saveToTextFile()
{
    // Input stream class to
    // operate on files.
    ifstream ifile("posts.txt", ios::in);

    // Output stream class to
    // operate on files.
    ofstream file("posts.txt", ios::out | ios::app);

    // check if file exists
    if (!ifile.is_open()) {

        // file not found (i.e, not opened).
        // Print an error message.
        cout << "file not found";
    }
    else {
        // then add more lines to
        // the file if need be
        file << title << "," << description << "," << username << "," << topic << endl;
        file.close();
    }

}

void Post::setLikeList(List<string> likeList)
{
    likeList = likeList;
}

List<string> Post::getLikeList()
{
    return likeList;
}

void Post::setReplies(Stack<Reply> replyStack)
{
    replies = replyStack;
}

Stack<Reply> Post::getReplies()
{
    return replies;
}

void Post::readTextFileByUser(User user)
{
    ifstream file("posts.txt");
    string line;
    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, desc, username, topic;
        getline(ss, title, ',');
        getline(ss, desc, ',');
        getline(ss, username, ',');
        getline(ss, topic, ',');
        if (user.getName() == username) {
            cout << "\n";
            cout << "Post " << count+1 << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| username | "  << setw(10) << username << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| Topic    | " << setw(10) << topic << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| Title    | " << setw(10) << title << "|" << endl;
            cout << "+----------------------+" << endl;
            cout << "| Content  | " << setw(10) << desc << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "\n";
            count++;
        }
    }
    file.close();
    if (count == 0) {
        cout << "You have not post yet." << endl;
    }

}

List<Post> Post::readTextFileByTopic(string topicName)
{
    ifstream file("posts.txt");
    string line;
    List<Post> list = List<Post>();
    List<string> likeList = List<string>();
    Stack<Reply> replyStack = Stack<Reply>();
    while (getline(file, line)) {
        stringstream ss(line);
        string title, desc, username, topic;
        getline(ss, title, ',');
        getline(ss, desc, ',');
        getline(ss, username, ',');
        getline(ss, topic, ',');
        if (topicName == topic) {
            Post p(title, desc, username, topic, likeList, replyStack);
            list.add(p);
        }
    }
    file.close();
    return list;
}
