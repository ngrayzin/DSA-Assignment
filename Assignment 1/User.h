/**
* Group: 7
* -----------------------------------
* Name Member 1:         Low Hong Wei
* Student ID Member 1:   S10203927J
*
* Name Member 2:         Ng Ray Zin
* Student ID Member 2:   S10222457
* ------------------------------------
*/
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

	/**
	* Description: Initalises the user class
	*/
	User();

	/**
	* Description:
	* Overloaded initalise user class function
	* 
	* Input:
	* Name of the user
	* Password of the user
	*/
	User(string n, string pw);

	/**
	* Description:
	* Sets a new name for the user
	* 
	* Input:
	* The new name
	* 
	* Output:
	* None
	*/
	void setName(string n);

	/**
	* Description:
	* Gets the name of the user
	*
	* Input:
	* None
	*
	* Output:
	* User's name
	*/
	string getName();

	/**
	* Description:
	* Sets a new password for the user
	*
	* Input:
	* The new password
	*
	* Output:
	* None
	*/
	void setPassword(string pw);

	/**Rayzin Help input here
	* Description:
	* 
	*
	* Input:
	* 
	*
	* Output:
	* None
	*/
	void saveToTextFile();

	/**
	* Description:
	* Get the user's password
	*
	* Input:
	* None
	*
	* Output:
	* User's password
	*/
	string getPassword();
};

