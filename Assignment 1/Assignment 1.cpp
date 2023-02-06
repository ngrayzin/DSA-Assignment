#include<string>
#include<iostream>
#include <sstream>
#include<fstream>
#include <iomanip>
#include "Dictionary.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "List.h"
#include "Stack.h"
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
using namespace std;

Dictionary<string> loadInfo();
Dictionary<List<Post>> loadTopic();
void displayMenu();
void login();
void printPost(Post post);
void postDetails(Post post, int i);
void userLogin(Dictionary<string> userData);
void userSignUp(Dictionary<string> userData);
void deleteAndEditOption();

static bool loggedIn = false;
User currentUser;


int main()
{
    Dictionary<string> userData = loadInfo();
    Dictionary<List<Post>> topicDict = loadTopic();
    List<Post> currentList;
    List<Post>* pointerList;
    Post* p;
    int option = 1;
    while (option != 0)
    {
        if (!loggedIn) {
            //show login page
            login();
            cin >> option;
            if (option == 1) {
                userLogin(userData);
            }
            else if (option == 2) {
                userSignUp(userData);
            }
            else if (option == 0) {
                cout << "BYEBYE" << endl;
            }
            else
                cout << "Invalid option! Please try again." << endl;
        }
        else {
            //show main page
            displayMenu();
            cin >> option;
            if (option == 1) {
                int userPostOption;
                pointerList = topicDict.search(currentUser.getName()); // print post
                cout << endl;
                deleteAndEditOption(); //Prints the option list
                cin >> userPostOption;
                if (userPostOption == 1) { //Editing Post
                    int editOrDeleteOption;
                    int OptionChoice;
                    cout << "Enter post number you want to delete/edit: ";
                    cin >> editOrDeleteOption;
                    Post* p = currentList.getAddress(editOrDeleteOption - 1);
                    List<Post> userPostList = topicDict.get(p->getTopic());
                    cout << UNDERLINE << "Enter what you want to do to this post: " << CLOSEUNDERLINE << endl << "[1] Edit Post's Description" << endl << "[2] Delete Post" << endl << "Enter Option: ";
                    cin >> OptionChoice;
                    if (OptionChoice == 1) {
                        string description = p->getDescription(); //Getting current description
                        int editChoice = true;
                        Stack<char> charStack;
                        for (int x = description.size(); x >= 0; x--) {//Splits the string description into char and adds it into new char stack
                            cout << description[x] << endl;
                            charStack.push(description[x]);
                        }
                        cout << charStack.top() << endl;
                        charStack = charStack.inverseStack();
                        charStack.pop(); //Removes additional white space that came when changing the string into char
                        cout << charStack.top() << endl;
                        //charStack.
                        while (editChoice) {
                            cout << "Current description: ";
                            charStack.printInversed(charStack);
                            cout << endl;
                            cout << "[1] Add to description" << endl;
                            cout << "[2] Delete some characters" << endl;
                            cout << "[3] Done editing" << endl;
                            cout << "Option: ";
                            cin >> editChoice;
                            if (editChoice == 1) {
                                string additionalWords;
                                charStack.printInversed(charStack);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Allows for spacing
                                getline(cin, additionalWords);
                                for (int i = 0; i < additionalWords.size(); i++) {//Splits the string input into char and adds it into new char stack
                                    charStack.push(additionalWords[i]);
                                }
                                charStack.printInversed(charStack);
                                cout << endl;
                            }
                            else if (editChoice == 2) {
                                int undoChoice = 1;
                                while (undoChoice == 1) {
                                    cout << "Current description: ";
                                    charStack.printInversed(charStack);
                                    cout << endl;
                                    cout << "[1] Undo" << endl << "[0] Quit: " << endl << "Option: ";
                                    cin >> undoChoice;
                                    if (undoChoice == 0) {
                                        break;
                                    }
                                    else if (undoChoice == 1) { //Removes the char when user wants to undo
                                        charStack.pop();
                                    }
                                }
                            }
                            else if (editChoice == 3) {
                                string newDescription = "";
                                int charStackLength = charStack.getLength();
                                charStack = charStack.inverseStack();
                                for (int c = 0; c < charStackLength; c++) { //Gets all the char from the stack and adds it into a string
                                    newDescription += charStack.top();
                                    charStack.pop();
                                }
                                p->setDescription(newDescription); //Sets new description
                                editChoice = false;
                            }
                            else {
                                cout << "Enter a valid option" << endl;
                            }
                        }
                    }
                    else if (OptionChoice == 2) {
                        pointerList->remove(*p);
                    }
                    else {
                        cout << "F";
                    }

                }
            }
            else if (option == 2) {
                string topicName;
                List<Post> postList;
                cout << "Enter the topic you want to create: ";
                cin >> topicName;
                Topic t(topicName, postList);
                if (topicDict.contain(topicName)) {
                    cout << "This topic already exist" << endl;
                }
                else {
                    topicDict.add(topicName, postList);
                    t.saveToTextFile();
                    cout << "created!" << endl;
                }
            }
            else if (option == 3) {
                string topicName;
                string title, desc;
                cout << "List of available topics:" << endl;
                topicDict.print();
                cout << "Enter what topic this post is about: ";
                cin >> topicName;
                if (topicDict.contain(topicName)) {
                    cout << "Enter the post's title: ";
                    cin >> title;
                    cout << "Enter the post's description: ";
                    cin >> desc;
                    Stack<Reply> s = Stack<Reply>();
                    List<string> l = List<string>();
                    Post p = Post(title, desc, currentUser.getName(), topicName, l, s);
                    topicDict.getAddress(topicName).add(p);
                    cout << "created!" << endl;
                    p.saveToTextFile();
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
            }
            else if (option == 4) {
                cout << "List of available topics:" << endl;
                topicDict.print();
                string topicName;
                cout << "Type the topic name that you would like to browse: ";
                cin >> topicName;
                if (topicDict.contain(topicName)) {
                    currentList = topicDict.get(topicName);
                    int i = 0;
                    cout << currentList.getLength() << endl;
                    for (i; i < currentList.getLength();i++) {
                        cout << "Post " << i + 1 << endl;
                        printPost(currentList.get(i));
                    }
                    if (i == 0) {
                        cout << "No post for this topic yet." << endl;
                    }
                    else {
                        int seePost;
                        cout << "Which post number you want to see: ";
                        cin >> seePost;
                        if (i >= seePost && 0 < seePost) {
                            p = currentList.getAddress(seePost - 1);
                            int detailOption = 1;
                            while (detailOption != 3) {
                                cout << "\n";
                                postDetails(*p, seePost);
                                cout << "Enter option: ";
                                cin >> detailOption;
                                if (detailOption == 1) {
                                    p->addLikes(currentUser.getName());
                                }
                                else if (detailOption == 2) {
                                    string replyMsg;
                                    cout << "Enter your message: ";
                                    cin >> replyMsg;
                                    p->addReply(replyMsg);
                                    cout << UNDERLINE << "Replies:" << CLOSEUNDERLINE << endl;
                                    p->printReplies();
                                    cout << endl;
                                }
                                else if (detailOption == 3) {
                                    cout << "back" << endl;
                                    Post save;
                                    save.updateTextFile(p);
                                }
                                else {
                                    cout << "invalid" << endl;
                                }
                            }
                        }
                        else {
                            cout << "Out of index." << endl;
                        }
                    }
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
            }
            else if (option == 5) {
                List<Post> p = topicDict.get("list");
                cout << p.getLength() << endl;
            }
            else if (option == 6) {
                loggedIn = false;
                cout << "Logged out" << endl;
            }
            else if (option == 0) {
                cout << "BYE BYE" << endl;
            }
            else
                cout << "Invalid option! Please try again." << endl;

        }
    }
}

Dictionary<string> loadInfo() {

    //read textfile then for loop make user add into dictionary
    Dictionary<string> d;
    ifstream file("users.txt");
    string line;

    while(getline(file, line)) {
        stringstream ss(line);
        string name, password, post;
        getline(ss, name, ',');
        getline(ss, password, ',');
        d.add(name, password);
    }
    file.close();
    return d;
}

Dictionary<List<Post>> loadTopic() {
    Dictionary<List<Post>> d = Dictionary<List<Post>>();
    Post p;
    string line;
    ifstream myfile("topics.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            List<Post> list = p.readTextFileByTopic(line);
            d.add(line, list);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
    return d;
}

void login()
{
    cout << endl;
    cout << "Welcome to forum     " << endl;
    cout << "---------------------" << endl;
    cout << "[1] Login            " << endl;
    cout << "[2] Sign up          " << endl;
    cout << "[0] Exit             " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}

void displayMenu()
{
    cout << endl;
    cout << "Main Menu            " << endl;
    cout << "---------------------" << endl;
    cout << "[1] View Your Posts  " << endl;
    cout << "[2] Create Topic     " << endl;
    cout << "[3] Create Post      " << endl;
    cout << "[4] Browse           " << endl;
    //cout << "[5] Edit/Delete Post " << endl;
    cout << "[5] Logout           " << endl;
    cout << "[0] Exit             " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}

void printPost(Post post) {
    cout << "+----------+-----------+" << endl;
    cout << "| username | " << setw(10) << post.getUser() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "| Topic    | " << setw(10) << post.getTopic() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "| Title    | " << setw(10) << post.getPostTitle() << "|" << endl;
    cout << "+----------------------+" << endl;
    cout << "| Content  | " << setw(10) << post.getDescription() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "\n";
}

void postDetails(Post post, int i) {
    cout << "Post " << i << endl;
    cout << "+----------+-----------+" << endl;
    cout << "| username | " << setw(10) << post.getUser() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "| Topic    | " << setw(10) << post.getTopic() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "| Title    | " << setw(10) << post.getPostTitle() << "|" << endl;
    cout << "+----------------------+" << endl;
    cout << "| Content  | " << setw(10) << post.getDescription() << "|" << endl;
    cout << "+----------+-----------+" << endl;
    cout << "Likes: " << post.getLikeList()->getLength() << endl;
    cout << "Comments: " << post.getReplies()->getLength() << endl;
    cout << "\n";
    cout << UNDERLINE << "Replies:" << CLOSEUNDERLINE << endl;
    post.printReplies();
    cout << endl;
    cout << "------------------------" << endl;
    if (post.getLikeList()->contain(currentUser.getName())) {
        cout << "[1] Unlike Post "  << i << endl;
        cout << "[2] Comment Post " << i << endl;
        cout << "[3] Back to browse" << endl;
    }
    else {
        cout << "[1] Like Post " << i << endl;
        cout << "[2] Comment Post " << i << endl;
        cout << "[3] Back to browse" << endl;
    }

}


void userLogin(Dictionary<string> userData) {
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (userData.contain(username, password)) {
        loggedIn = true;
        currentUser = User(username, password);
        cout << "Successful" << endl;
    }
    else {
        cout << "Wrong credentials" << endl;
    }
}

void userSignUp(Dictionary<string> userData) 
{
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    while (userData.contain(username)){
        cout << "Username is taken, please enter another name: ";
        cin >> username;
    }
    cout << "Enter password: ";
    cin >> password;
    if (userData.add(username, password)) {
        loggedIn = true;
        currentUser = User(username, password);
        //write to txt file
        currentUser.saveToTextFile();
        cout << "Successful" << endl;
    }
    else {
        cout << "oops something went wrong" << endl;
    }
   
}

void deleteAndEditOption() {
    cout << "[1] Edit/Delete Post" << endl;
    cout << "[2] Back to browse" << endl;
    cout << "Enter option: ";
}
