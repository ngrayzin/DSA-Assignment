#include<string>
#include<iostream>
#include <sstream>
#include<fstream>
#include <vector>
#include "Dictionary.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "List.h"
using namespace std;

Dictionary<string> loadInfo();
void displayMenu();
void login();
void userLogin(Dictionary<string> userData);
void userSignUp(Dictionary<string> userData);

static bool loggedIn = false;
User currentUser;


int main()
{
    List<string> list = List<string>(); // this type should be the post class e.g. List<Post> 
    //list.add("user", "title", "content"); //add the post in the list
    //list.add("user2", "bye", "bye");
    list.add("user2bye");
    Dictionary<List<string>> topicList = Dictionary<List<string>>(); // dictionary for topic : postList

    topicList.add("topic", list); // add the topic and post into the dic

    List<string> newList = topicList.get("topic");

    cout << list.getLength() << endl;

    cout << newList.getLength() << endl;


    //newList.print();
    Dictionary<string> userData = loadInfo();
    Dictionary<Topic> topicDict;
    cout << userData.getLength() << endl;
    
    int option = 1;
    while (option != 0)
    {
        if (!loggedIn) {
            //show login page
            login();
            cin >> option;
            if (option == 1) {
                userLogin(userData);
            }
            else if (option == 2) {
                userSignUp(userData);
            }
            else if (option == 0) {
                cout << "BYEBYE" << endl;
            }
            else
                cout << "Invalid option! Please try again." << endl;
        }
        else {
            //show main page
            displayMenu();
            cin >> option;
            if (option == 1) {
                cout << "option1" << endl;
            }
            else if (option == 2) {
                string titleName;
                List<Post> postList;
                cout << "Enter the topic you want to create: ";
                cin >> titleName;
                Topic t(titleName, postList);
                topicDict.add(titleName,t);
                Topic g = topicDict.get(titleName);
                cout << g.getPosts().getLength() << endl;
                cout << g.getTopic() << endl;

            }
            else if (option == 3) {
                string postTopic;
                string title;
                string desc;
                //currentUser
                cout << "Enter the post's title: ";
                cin >> title;
                cout << "Enter the post's description: ";
                cin >> desc;
                cout << "Enter what topic this post is about: ";
                cin >> postTopic;
                if (topicDict.check(postTopic) == true) {
                    Post p(title, desc, currentUser);
                    Topic currentTopic = topicDict.get(postTopic);
                    //List<Post> postList = topicDict.get(postTopic).getPosts();
                    int addedPost = currentTopic.addPost(p);
                    cout << addedPost << endl;
                    //currentTopic.getPosts()
                    //topicDict.get(postTopic).addPost(p);
                    //postList.print();
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
                
            }
            else if (option == 4) {
                if (topicDict.getLength() > 0) {
                    topicDict.printTopic();
                }
                else {
                    cout << "Nothing to print" << endl;
                }
            }
            else if (option == 5) {
                cout << "option5" << endl;
            }
            else if (option == 6) {
                loggedIn = false;
                cout << "Logged out" << endl;
            }
            else if (option == 0) {
                cout << "BYE BYE" << endl;
            }
            else
                cout << "Invalid option! Please try again." << endl;

        }
    }
}

Dictionary<string> loadInfo() {

    //read textfile then for loop make user add into dictionary
    Dictionary<string> d;
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, password, post;
        getline(ss, name, ',');
        getline(ss, password, ',');
        vector<string> posts;
        while (getline(ss, post, ',')) posts.push_back(post);
        d.add(name, password);
        cout << "posts: ";
        for (const auto& post : posts) {
            //here is where you populate the posts dictionary
            //im thinking have two itemtype (if possible) e.g. Key: Topic Itemtype1: name Itemtype 2: post
            //the replies i planning to store it in diff txt file so maybe each post have a txt file for itself
            cout << post << " ";
        } 
        cout << "\n";
    }
    file.close();
    return d;
}

void login()
{
    cout << endl;
    cout << "Welcome to nibba land" << endl;
    cout << "---------------------" << endl;
    cout << "[1] Login         " << endl;
    cout << "[2] Sign up            " << endl;
    cout << "[0] Exit            " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}

void displayMenu()
{
    cout << endl;
    cout << "Main Menu            " << endl;
    cout << "---------------------" << endl;
    cout << "[1] View Your Posts  " << endl;
    cout << "[2] Create Topic     " << endl;
    cout << "[3] Create Post      " << endl;
    cout << "[4] Browse           " << endl;
    cout << "[5] Edit/Delete Post " << endl;
    cout << "[6] Logout           " << endl;
    cout << "[0] Exit             " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}

void userLogin(Dictionary<string> userData) {
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (userData.check(username, password)) {
        loggedIn = true;
        currentUser = User(username, password);
        cout << "Successful" << endl;
    }
    else {
        cout << "Wrong credentials" << endl;
    }
}

void userSignUp(Dictionary<string> userData) 
{
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    while (userData.check(username)){
        cout << "Username is taken, please enter another name: ";
        cin >> username;
    }
    cout << "Enter password: ";
    cin >> password;
    if (userData.add(username, password)) {
        loggedIn = true;
        currentUser = User(username, password);
        //write to txt file
        currentUser.saveToTextFile();
        cout << "Successful" << endl;
    }
    else {
        cout << "oops something went wrong" << endl;
    }
   
}
