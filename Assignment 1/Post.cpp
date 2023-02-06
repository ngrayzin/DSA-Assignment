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
#include <vector>

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
    sticky = false;
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

void Post::setLikeList(List<string> list)
{
    likeList = list;
}

void Post::addLikes(string name)
{
    if (likeList.contain(name)) {
        likeList.remove(name); //unlike post :(
        Post p;
       // p.deleteFromTextFile(title, description, username, topic, name);
    }
    else {
        likeList.add(name);//like post :3
        //likeList.saveToTextFile(title, description, username, topic);
    }
}

List<string>* Post::getLikeList()
{
    return &likeList;
}


void Post::addReply(string msg) {
    Reply newReply(msg);
    replies.push(newReply);
    //replies.saveToTextFile(title, description, username, topic);
}

void Post::setReplies(Stack<Reply> replyStack)
{
    replies = replyStack;
}

void Post::printReplies() {
    int count = 1;
    Stack<Reply> replyList = replies.inverseStack();
    printReplies(count, replyList);
}

void Post::printReplies(int count,Stack<Reply> replyList) {
    if (replyList.isEmpty()) {
        return;
    }
    Reply r = replyList.top();
    replyList.pop();
    cout << "[" << count << "] " << r.getReply() << endl;
    printReplies(count+1,replyList);
    replyList.push(r);
}

Stack<Reply> *Post::getReplies()
{
    return &replies;
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


void Post::updateTextFile(Post p)
{
    // Read the existing contents into a vector of strings
    vector<string> lines;
    ifstream ifile("posts.txt", ios::in);
    string line;
    while (getline(ifile, line)) {
        stringstream ss(line);
        string title, desc, username, topic;
        getline(ss, title, ',');
        getline(ss, desc, ',');
        getline(ss, username, ',');
        getline(ss, topic, ',');
        if (title == p.getPostTitle() && desc == p.getDescription() && username == p.getUser() && topic == p.getTopic()) {
            // If the line is the post that needs to be updated, replace it with the updated post
            line = p.toString();
        }
        lines.push_back(line);
    }
    ifile.close();

    // Write the vector of strings back to the file
    ofstream ofile("posts.txt", ios::out);
    for (auto& l : lines)
        ofile << l << endl;
    ofile.close();
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
            cout << "Post " << count + 1 << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| username | " << setw(10) << username << "|" << endl;
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
    while (getline(file, line)) {
        List<string> likeList = List<string>();
        Stack<Reply> replyStack = Stack<Reply>();
        stringstream ss(line);
        string title, desc, username, topic, reply, likes;
        getline(ss, title, ',');
        getline(ss, desc, ',');
        getline(ss, username, ',');
        getline(ss, topic, ',');
        getline(ss, reply, ',');
        getline(ss, likes, ',');
        vector<string> stack = split(reply, ':');
        for (auto i : stack) {
            Reply r(i);
            replyStack.push(r);
        }
        vector<string> like = split(likes, '.');
        for (auto r : like) {
            likeList.add(r);
        } 
        if (topicName == topic) {
            Post p(title, desc, username, topic, likeList, replyStack);
            list.add(p);
        }
    }
    file.close();
    return list;
}

vector<string> Post::split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    if (ss) {
        result.push_back(ss.str());
    }

    return result;
}

string Post::toString()
{
    string line = title + "," + description + "," + username + "," + topic + ",";
    Stack<Reply> replyList = replies.inverseStack();
    List<Reply> newlist = replyList.toList();
    cout << newlist.getLength() << endl;
    int i = 0;
    if (newlist.getLength() > 0) {
        for (i; i < newlist.getLength(); i++) {
            line += newlist.get(i).getReply() + ":";
        }
    }
    line += ",";
    for (int r = 0; r < likeList.getLength(); r++) {
        line += likeList.get(r) + ".";
    }

    return line;
}
List<Post> Post::returnPostListByUser(User user)
{
    ifstream file("posts.txt");
    string line;
    int count = 0;
    List<Post> userPostList;
    while (getline(file, line)) {
        List<string> likeList = List<string>();
        Stack<Reply> replyStack = Stack<Reply>();
        stringstream ss(line);
        string title, desc, username, topic;
        getline(ss, title, ',');
        getline(ss, desc, ',');
        getline(ss, username, ',');
        getline(ss, topic, ',');
        if (user.getName() == username) {
            cout << "\n";
            cout << "Post " << count + 1 << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| username | " << setw(10) << username << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| Topic    | " << setw(10) << topic << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "| Title    | " << setw(10) << title << "|" << endl;
            cout << "+----------------------+" << endl;
            cout << "| Content  | " << setw(10) << desc << "|" << endl;
            cout << "+----------+-----------+" << endl;
            cout << "\n";
            count++;
            Post p(title, desc, username, topic, likeList, replyStack);
            userPostList.add(p);
        }
    }
    file.close();
    if (count == 0) {
        cout << "You have not post yet." << endl;
    }
    return userPostList;

}

bool Post::operator==(const Post& rhs) {
    cout << title << topic << endl;
    cout << rhs.title << topic << endl;
    bool f = title == rhs.title;
    cout << f << endl;
    return (title == rhs.title);
}

bool Post::getSticky() {
    if (sticky) {
        return true;
    }
    else {
        return false;
    }
}

void Post::setSticky() {
    sticky = true;
}