#pragma once
#include<string>
#include<iostream>
#include"Dictionary.h"
using namespace std;

class User 
{

private:
	string name;
	string password;

public:
	User();
	User(string n, string pw);
	void setName(string n);
	string getName();
	void setPassword(string pw);
	void saveToTextFile();
	string getPassword();
};

