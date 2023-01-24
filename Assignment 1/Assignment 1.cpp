#include<string>
#include<iostream>
#include <sstream>
#include<fstream>
#include <vector>
#include "Dictionary.h"
#include "User.h"
using namespace std;

Dictionary loadInfo();
void displayMenu();
void login();
void userLogin();
void userSignUp();

Dictionary userData;
static bool loggedIn = false;
User currentUser;


int main()
{
    
    userData = loadInfo();
    int option = 1;
    while (option != 0)
    {
        if (!loggedIn) {
            //show login page
            login();
            cin >> option;
            if (option == 1) {
                userLogin();
            }
            else if (option == 2) {
                userSignUp();
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
                cout << "option2" << endl;
            }
            else if (option == 3) {
                cout << "option3" << endl;
            }
            else if (option == 4) {
                cout << "option4" << endl;
            }
            else if (option == 5) {
                cout << "option5" << endl;
            }
            else if (option == 0) {
                cout << "BYEBYE" << endl;
            }
            else
                cout << "Invalid option! Please try again." << endl;

        }
    }
    
    return 0;

}

Dictionary loadInfo() {
    //read textfile then for loop make user add into dictionary
    Dictionary d;
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

    d.print();
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
    cout << "[0] Exit             " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}

void userLogin() {
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (userData.returnLogin(username, password)) {
        loggedIn = true;
        currentUser = User(username, password);
        cout << "Successful" << endl;
    }
    else {
        cout << "Wrong credentials" << endl;
    }
}

void userSignUp() {
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    while (userData.validateLogin(username)){
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
