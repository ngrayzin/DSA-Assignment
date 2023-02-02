#include "User.h"
#include"Dictionary.h"
#include<fstream>
#include "Post.h"

User::User() {}

User::User(string n, string pw)
{
	name = n;
	password = pw;
}

void User::setName(string n) { name = n; }

string User::getName(){return name;}

void User::setPassword(string pw){password = pw;}

string User::getPassword() { return password; }


void User::saveToTextFile()
{
    // Input stream class to
    // operate on files.
    ifstream ifile("users.txt", ios::in);

    // Output stream class to
    // operate on files.
    ofstream file("users.txt", ios::out | ios::app);

    // check if file exists
    if (!ifile.is_open()) {

        // file not found (i.e, not opened).
        // Print an error message.
        cout << "file not found";
    }
    else {
        // then add more lines to
        // the file if need be
        file << name << "," << password <<  endl;
        file.close();
    }

}

