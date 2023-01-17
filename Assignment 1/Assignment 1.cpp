#include<string>
#include<iostream>
#include "Dictionary.h"
#include "User.h"
using namespace std;

void loadInfo();
void displayMenu();
void login();
void userLogin();
void userSignUp();

Dictionary userData;
static bool loggedIn = false;

int main()
{
    loadInfo();
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

void loadInfo() {
    //read textfile then for loop make user add into dictionary
    //userData.add(userId, User class)
    User u1;
    u1.setName("billy");
    u1.setPassword("123456");
    User u2;
    u2.setName("niasd");
    u2.setPassword("123456");
    User u3;
    u3.setName("asdaaa");
    u3.setPassword("123456");
    User u4 = User("etst", "123234");

    userData.add("billy", "123456");
    userData.add("niasd", "123456");
    userData.add("asdaaa", "123456");
    userData.add("etst", "123456");
    userData.print();
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
    cout << "Enter password: ";
    cin >> password;
    if (userData.add(username, password)) {
        loggedIn = true;
        //write to txt file
        cout << "Successful" << endl;
    }
    else {
        cout << "oops something went wrong" << endl;
    }
   
}
