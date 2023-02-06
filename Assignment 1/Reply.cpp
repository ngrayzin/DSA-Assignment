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
#include <string>
#include <iostream>
#include "Reply.h"
using namespace std;

Reply::Reply() {}

Reply::Reply(string r) {
    reply = r;
}

void Reply::updateReply(string r) {
    reply = r;
}

string Reply::getReply() {
    return reply;
}