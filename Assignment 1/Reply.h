#include "Stack.h"
#include <iostream>
#include <string>
#pragma once

class Reply {
private:
    string reply;

public:
    Reply();
    Reply(string reply);
    void updateReply(string newReply);
    string getReply();
};