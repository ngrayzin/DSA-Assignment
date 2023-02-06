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
#include <iostream>
#include <string>
using namespace std;

class Reply
{

private:
    string reply;

public:
    /**
    * Description:
    * Initialises the Reply class
    */
    Reply();

    /**
    * Description:
    * Overloaded initialise function for reply class
    *
    * Input:
    * reply message
    *
    */
    Reply(string reply);

    /**
    * Description:
    * Updates the reply message with a new one
    *
    * Input:
    * New reply message
    *
    * Output:
    * None
    */
    void updateReply(string newReply);

    /**
    * Description:
    * Gets the string reply message
    *
    * Input:
    * None
    *
    * Output:
    * Reply message in string form
    */
    string getReply();
};