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