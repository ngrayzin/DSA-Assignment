#include "User.h"
int User::unique_id = 0;

User::User() {
	userId = unique_id++;
}

User::User(string n, string pw)
{
	name = n;
	password = pw;
}

void User::setName(string n) { name = n; }

string User::getName(){return name;}

void User::setPassword(string pw){password = pw;}

int User::getId() { return userId; }

