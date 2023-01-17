#pragma once

#include<string>
#include<iostream>
using namespace std;

class User
{

private:
	string name;
	string password;
	int userId;
	static int unique_id;

public:
	User();
	User(string n, string pw);
	void setName(string n);
	string getName();
	void setPassword(string pw);
	int getId();
};

