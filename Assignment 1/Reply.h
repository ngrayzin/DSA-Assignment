#include "Stack.h"
#include <iostream>
#include <string>
#pragma once

class Reply {
public:
    string reply;

private:
    Reply();
    Reply(string reply);
    void updateReply(string newReply);
    string getReply();
};