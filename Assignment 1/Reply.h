#pragma once
#include <iostream>
#include <string>
using namespace std;

class Reply
{

private:
    string reply;

public:
    Reply();
    Reply(string reply);
    void updateReply(string newReply);
    string getReply();
};