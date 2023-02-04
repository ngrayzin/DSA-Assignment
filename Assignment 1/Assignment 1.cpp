#include<string>
#include<iostream>
#include <sstream>
#include<fstream>
#include <iomanip>
#include "Dictionary.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "List.h"
#include "Stack.h"
using namespace std;

Dictionary<string> loadInfo();
Dictionary<List<Post>> loadTopic();
void displayMenu();
void login();
void userLogin(Dictionary<string> userData);
void userSignUp(Dictionary<string> userData);

static bool loggedIn = false;
User currentUser;


int main()
{
    Dictionary<string> userData = loadInfo();
    Dictionary<List<Post>> topicDict = loadTopic();
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
                Post p;
                p.readTextFileByUser(currentUser);
            }
            else if (option == 2) {
                string topicName;
                List<Post> postList;
                cout << "Enter the topic you want to create: ";
                cin >> topicName;
                Topic t(topicName, postList);
                topicDict.add(topicName, postList);
                t.saveToTextFile();
            }
            else if (option == 3) {
                string topicName;
                string title, desc;
                cout << "List of available topics:" << endl;
                topicDict.print();
                cout << "Enter what topic this post is about: ";
                cin >> topicName;
                if (topicDict.contain(topicName)) {
                    cout << "Enter the post's title: ";
                    cin >> title;
                    cout << "Enter the post's description: ";
                    cin >> desc;
                    Post p = Post(title, desc, currentUser.getName(), topicName);
                    topicDict.get(topicName).add(p);
                    p.saveToTextFile();
                    cout << topicDict.get(topicName).getLength() << endl;
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
            }
            else if (option == 4) {
                cout << "List of available topics:" << endl;
                topicDict.print();
                string topicName;
                cout << "Which topic would you like to browse: ";
                cin >> topicName;
                if (topicDict.contain(topicName)) {
                    List<Post> list = topicDict.get(topicName);
                    int i = 0;
                    for (i; i < list.getLength();i++) {
                        cout << "Post " << i + 1 << endl;
                        cout << "+----------+-----------+" << endl;
                        cout << "| username | " << setw(10) << list.get(i).getUser() << "|" << endl;
                        cout << "+----------+-----------+" << endl;
                        cout << "| Topic    | " << setw(10) << list.get(i).getTopic() << "|" << endl;
                        cout << "+----------+-----------+" << endl;
                        cout << "| Title    | " << setw(10) << list.get(i).getPostTitle() << "|" << endl;
                        cout << "+----------------------+" << endl;
                        cout << "| Content  | " << setw(10) << list.get(i).getDescription() << "|" << endl;
                        cout << "+----------+-----------+" << endl;
                        cout << "\n";
                    }
                    if (i == 0) {
                        cout << "No post for this topic yet." << endl;
                    }
                    if (i > 0) {
                        int replyOption;
                        cout << "Would you like to reply to any of these?" << endl << "[1] Yes" << endl << "[2] No" << endl << "Enter your option: ";
                        cin >> replyOption;
                        

                        if (replyOption == 1) {
                            string replyTitle;
                            cout << "Enter the title of the post you would like to reply to: ";
                            cin >> replyTitle;
                        }
                    }
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
            }
            else if (option == 5) {
                Stack<string> s;
                string i;
                cout << s.isEmpty() << endl;
                s.push("POPOPOP");
                s.push("PEPEPEPEPE");
                s.push("SHESHESHESHE");
                s.displayInOrder();
                s.pop(i);
                cout << s.isEmpty() << endl;
                cout << i << endl;
                cout << endl;
                s.clear(s);
                s.displayInOrderOfInsertion();
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
        d.add(name, password);
    }
    file.close();
    return d;
}

Dictionary<List<Post>> loadTopic() {
    Dictionary<List<Post>> d = Dictionary<List<Post>>();
    Post p;
    string line;
    ifstream myfile("topics.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            List<Post> list = p.readTextFileByTopic(line);
            d.add(line, list);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
    return d;
}

void login()
{
    cout << endl;
    cout << "Welcome to forum     " << endl;
    cout << "---------------------" << endl;
    cout << "[1] Login            " << endl;
    cout << "[2] Sign up          " << endl;
    cout << "[0] Exit             " << endl;
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
    if (userData.contain(username, password)) {
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
    while (userData.contain(username)){
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
