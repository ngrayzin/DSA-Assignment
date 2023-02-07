/**
* Group: 7
* -----------------------------------
* Name Member 1:         Low Hong Wei
* Student ID Member 1:   S10203927J
* 
* Name Member 2:         Ng Ray Zin
* Student ID Member 2:   S10222457H
* ------------------------------------
*/

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

//Explanation of functions below
Dictionary<string> loadInfo();
Dictionary<List<Post>> loadTopic();
void displayMenu();
void login();
void printPost(Post post);
void postDetails(Post post, int i);
void userLogin(Dictionary<string> userData);
void userSignUp(Dictionary<string> userData);
void deleteAndEditOption();
void printSticky(int length, List<Post> p, int& count);
void printStickyByUser(int length, List<Post> p, int& count);
void wrapText(const string& text, int width);
static bool loggedIn = false;
User currentUser;


int main()
{
    Dictionary<string> userData = loadInfo(); //fill up the dictionary with user data where key is their username and itemtype is their password
    Dictionary<List<Post>> topicDict = loadTopic(); //fill up the dictionary with topic and List<Post> data where the key is the topic name and the itemtype is a List<Post>
    List<Post>* currentList; //A pointer post list
    List<Post>* pointerList; //A pointer post list
    Post* p; //Post pointer used to edit the chosen post
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
            if (option == 1) { //View Your Posts
                int userPostOption;
                cout << "List of available topics:" << endl;
                topicDict.print(); //Prints out the different topics inside the hash table
                string userTopicName;
                cout << "Type the topic name that you would like to browse: ";
                cin >> userTopicName;
                if (topicDict.contain(userTopicName)) {//Checks if the hash table has the specified topic entered by the user
                    currentList = topicDict.get(userTopicName); //If yes then it will get the list filled with post that belongs to that topic
                    int userPostCount = 0; //How many posts users have in that topic
                    int currentListLength = currentList->getLength(); //Length of the whole topic list including those that weren't created by user
                    printStickyByUser(currentListLength, *currentList,userPostCount); 
                    if (userPostCount == 0) { //No posts by user
                        cout << "No post for this topic yet." << endl;
                    }
                    else {
                        int seePost;
                        cout << "Which post number you want to see: ";
                        cin >> seePost;
                        int i = 0;

                        if (seePost <= currentListLength && 0 < seePost && currentList->get(seePost-1).getUser() == currentUser.getName()) { //validation to stop users from updating other people's post as well as index out of the list
                            p = currentList->getAddress(seePost - 1); //Gets the post pointer which the user specified they want to view
                            cout << endl;
                            deleteAndEditOption(); //Prints the option list
                            cin >> userPostOption;
                            if (userPostOption == 1) { //Editing Post
                                int OptionChoice;
                                cout << UNDERLINE << "Enter what you want to do to this post: " << CLOSEUNDERLINE << endl;
                                cout << "[1] Edit Post's Description" << endl << "[2] Delete Post" << endl << "Enter Option: ";
                                cin >> OptionChoice;
                                if (OptionChoice == 1) {
                                    string description = p->getDescription(); //Getting current description
                                    int editChoice = true;
                                    Stack<char> charStack;
                                    for (int x = description.size(); x >= 0; x--) {//Splits the string description into char and adds it into new char stack
                                        charStack.push(description[x]);
                                    }
                                    charStack = charStack.inverseStack(); //inverse the stack so that the new string will be added correctly
                                    charStack.pop(); //Removes additional white space that came when changing the string into char
                                    //charStack.
                                    while (editChoice) {
                                        cout << "Current description: ";
                                        charStack.printInversed(charStack); //Prints the description
                                        cout << endl;
                                        cout << "[1] Add to description" << endl;
                                        cout << "[2] Delete some characters" << endl;
                                        cout << "[3] Done editing" << endl;
                                        cout << "Option: ";
                                        cin >> editChoice;
                                        if (editChoice == 1) {
                                            string additionalWords;
                                            charStack.printInversed(charStack); //Prints the description so the user has an idea of what they want to add
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Allows for spacing
                                            getline(cin, additionalWords);
                                            for (int i = 0; i < additionalWords.size(); i++) {//Splits the string input into char and adds it into new char stack
                                                charStack.push(additionalWords[i]);
                                            }
                                            cout << endl;
                                        }
                                        else if (editChoice == 2) { //Undo feature character
                                            int undoChoice = 1;
                                            while (undoChoice == 1) { //Undo
                                                cout << "Current description: ";
                                                charStack.printInversed(charStack); //Shows current description
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
                                        else if (editChoice == 3) { //Done editing
                                            string newDescription = ""; 
                                            int charStackLength = charStack.getLength();
                                            charStack = charStack.inverseStack(); //Inverse it back so the new string wont be opposite
                                            for (int c = 0; c < charStackLength; c++) { //Gets all the char from the stack and adds it into a string
                                                newDescription += charStack.top(); //Gets the top of the stack and adds it into the previously empty variable
                                                charStack.pop();//Removes it so the next top will be different
                                            }
                                            p->setDescription(newDescription); //Sets new description
                                            p->updateTextFile(p);//writes into the text file
                                            editChoice = false; //break
                                        }
                                        else {
                                            cout << "Enter a valid option" << endl;
                                        }
                                    }
                                }
                                else if (OptionChoice == 2) { //Delete Post
                                    List<Post>* postTopicList = topicDict.get(userTopicName); //Gets referenced post list under the chosen topic
                                    postTopicList->remove(*p); //uses the remove function to remove based on post class. The remove function uses the operator== function to equate the Post to another Post
                                    p->DeleteFromTextFile(p); //Rayzin Help input here
                                    cout << "Deleted Post!" << endl;
                                }
                                else {
                                    cout << "Please enter a valud option" << endl;
                                }
                            }
                        }
                        else {
                            cout << "Out of index." << endl;
                        }
                    }
                }
                else {
                    cout << "No such topic" << endl;
                }
            }
            else if (option == 2) { //Create Topic
                string topicName;
                List<Post> postList; //Empty post list as there can't be a post before the topic has been created
                cout << "Enter the topic you want to create: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, topicName);
                Topic t(topicName, postList);//Creates a topic class with the topic name and empty post list
                if (topicDict.contain(topicName)) { //Validation to check whether the topic is already inserted into the list
                    cout << "This topic already exist" << endl;
                }
                else {
                    topicDict.add(topicName, postList); //Add the newly created topic class into the dictionary
                    cout << "created!" << endl;
                }
            }
            else if (option == 3) { //Create Post
                string topicName;
                string title, desc;
                cout << "List of available topics:" << endl;
                topicDict.print();
                cout << "Enter what topic this post is about: ";
                cin >> topicName;
                if (topicDict.contain(topicName)) {//Checks if the topic entered is inside the topic dictionary
                    cout << "Enter the post's title: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Allows for spacing
                    getline(cin, title);
                    currentList = topicDict.get(topicName);
                    bool dupe = false;
                    for (int i = 0; i < currentList->getLength(); i++) {
                        if (currentList->get(i).getPostTitle() == title) {
                            cout << "There is already a post about this! Check it out" << endl;
                            dupe = true;
                            break;
                        }
                    }
                    if (dupe == false) {
                        cout << "Enter the post's description: "; //Allows for spacing
                        getline(cin, desc);
                        Stack<Reply> s = Stack<Reply>(); //Empty reply list as there cannot be a reply before the post was created
                        List<string> l = List<string>(); //Empty like list as there cannot be any likes before the post was created
                        Post p = Post(title, desc, currentUser.getName(), topicName, l, s); //Making of the post class to be inserted later
                        topicDict.getAddress(topicName).add(p); //Gets the reference of the post list based on the topic entered by user and adds a post into that list
                        cout << "created!" << endl;
                        p.saveToTextFile(); //Rayzin Help input here
                    }
                }
                else {
                    cout << "Sorry, there is no topic that matches the one specified. Try again!" << endl;
                }
            }
            else if (option == 4) { //browse
                cout << "List of available topics:" << endl;
                topicDict.print(); // this prints out all theh available topics
                string topicName;
                cout << "Type the topic name that you would like to browse: "; //gets topic name input from user 
                cin >> topicName;
                if (topicDict.contain(topicName)) { //if the dictionary contains the topic name
                    currentList = topicDict.get(topicName); // then get the List<Post> from the key
                    int i = 0;
                    printSticky(currentList->getLength(), *currentList, i); //prints out all the post with a post index
                    /*for (i; i < currentList->getLength(); i++) {
                        cout << "Post " << i + 1 << endl;
                        printPost(currentList->get(i));
                    }*/
                    if (i == 0) {
                        cout << "No post for this topic yet." << endl; //if counter is 0, means there are no post for this topic
                    }
                    else {
                        int seePost;
                        cout << "Which post number you want to see: "; //prompt user for post index
                        cin >> seePost;
                        if (i >= seePost && 0 < seePost) { //if the index is within the post index range
                            p = currentList->getAddress(seePost - 1); //gets the pointer for the Post in the list
                            int detailOption = 1;
                            while (detailOption != 3) { //this while statment is for users to see the post details
                                cout << "\n";
                                postDetails(*p, seePost);//prints the entire post in detail
                                cout << "Enter option: ";
                                cin >> detailOption;
                                if (detailOption == 1) {
                                    p->addLikes(currentUser.getName()); //like the post and updates the likelist for that post
                                }
                                else if (detailOption == 2) {
                                    string replyMsg;
                                    cout << "Enter your message: ";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Allows for spacing
                                    getline(cin, replyMsg);
                                    p->addReply(replyMsg); //reply to the post and update the reply stack for that post
                                    cout << endl;
                                    /*cout << UNDERLINE << "Replies:" << CLOSEUNDERLINE << endl;
                                    p->printReplies();
                                    */
                                }
                                else if (detailOption == 3) {
                                    cout << "back" << endl;
                                    Post save;
                                    save.updateTextFile(p); ///save all changes the user have made and write back into the text file
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
            else if (option == 5) { //Pin topic
                int userPostOption;
                cout << "List of available topics:" << endl;
                topicDict.print();
                string userTopicName;
                cout << "Enter a topic name: ";
                cin >> userTopicName;
                if (topicDict.contain(userTopicName)) {
                    currentList = topicDict.get(userTopicName); //Get reference post list by topic name
                    int postPrinted = 0;
                    int pinnedPost;
                    int currentListLength = currentList->getLength();
                    printSticky(currentListLength, *currentList, postPrinted);//prints the current list but prints the sticky note posts first if there are any
                    cout << "Enter the post number that you want to pin: ";
                    cin >> pinnedPost;
                    if (pinnedPost > 0 && pinnedPost <= currentListLength) { //Validation to stop user from pinning other peoples post
                        p = currentList->getAddress(pinnedPost-1);
                        p->setSticky();
                        cout << "Pinned!" << endl << endl;
                    }
                    else {
                        cout << "Invalid choice! Did not pin" << endl;
                    }
                }

            }
            else if (option == 6) {// Log out option
                loggedIn = false; //sets the loggedIn to false and redirect to the login page
                cout << "Logged out" << endl;
            }
            else if (option == 0) {
                cout << "BYE BYE" << endl; //exit program
            }
            else
                cout << "Invalid option! Please try again." << endl;

        }
    }
}


/**
* Description:
* This function is to load and fill the user dictinoary when the program first starts
* 
* Input:
* None
* 
* Output:
* userData
*/
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


/**
* Description:
* This function is to load and fill the topic dictionary when the program first starts
*
* Input:
* None
*
* Output:
* topicDict
*/
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


/**
* Description:
* Simple function that prints out the UI for the login page
*
* Input:
* None
*
* Output:
* Printed statement
*/
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


/**
* Description:
* Simple function that prints the options for the main menu
*
* Input:
* None
*
* Output:
* Printed statement
*/
void displayMenu()
{
    cout << endl;
    cout << "Main Menu            " << endl;
    cout << "---------------------" << endl;
    cout << "[1] View Your Posts  " << endl;
    cout << "[2] Create Topic     " << endl;
    cout << "[3] Create Post      " << endl;
    cout << "[4] Browse           " << endl;
    cout << "[5] Pin Topic        " << endl;
    cout << "[6] Logout           " << endl;
    cout << "[0] Exit             " << endl;
    cout << "---------------------" << endl;
    cout << "Enter your option: ";
}


/**
* Description:
* A function that helps print some of the  post content 
*
* Input:
* None
*
* Output:
* Printed statment
*/
void printPost(Post post) {
    int width = post.getPostTitle().length() + 19;
    string cover = string(width, '-');
    int spaces = (width - post.getPostTitle().length() - 2) / 2;
    cout << "+" + cover + "+" << endl;
    cout << "|";
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << post.getPostTitle();
    for (int i = 0; i < width - spaces - post.getPostTitle().length(); i++)
        cout << " ";
    cout << "|" << endl;
    cout << "+" + cover + "+" << endl;
    cout << "Post by: " << post.getUser() << endl;
    cout << "Topic: "<< post.getTopic() << endl;
    cout << "Likes: " << post.getLikeList()->getLength() << endl;
    cout << "Replies: " << post.getReplies()->getLength() << endl;
    cout << "+" + cover + "+" << endl;
    cout << "\n";
}


/**
* Description:
* A function that helps print all the post content 
*
* Input:
* None
*
* Output:
* Printed statement
*/
void postDetails(Post post, int i) {
    cout << "Post " << i << endl;
    int width = post.getPostTitle().length() + 19;
    string cover = string(width, '-');
    cout << "+" + cover + "+" << endl;
    int spaces = (width - post.getPostTitle().length() - 2) / 2;
    cout << "|";
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << post.getPostTitle();
    for (int i = 0; i < width - spaces - post.getPostTitle().length(); i++)
        cout << " ";
    cout << "|" << endl;
    cout << "+" + cover + "+" << endl;
    wrapText(post.getDescription(), width);
    cout << "-" + cover + "-" << endl;
    cout << "Topic: " << post.getTopic() << endl;
    cout << "Posted by: " << post.getUser() << endl;
    cout << "Likes: " << post.getLikeList()->getLength() << endl;
    cout << "Replies: " << post.getReplies()->getLength() << endl;
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


/**
* Description:
* This function is to make sure the description of the post keeps within a width
*
* Input:
* None
*
* Output:
* Printed statement
*/
void wrapText(const string& text, int width) {
    istringstream iss(text);
    string word;
    string line;
    while (iss >> word) {
        if (line.length() + word.length() + 1 > width) {
            cout << line << endl;
            line = "";
        }
        if (line.empty()) {
            line = word;
        }
        else {
            line += " " + word;
        }
    }
    cout << line << endl;
}

/**
* Description:
* This fucntion is the prompt for the user login, if successful, 
* it will make loggedIn true; otherwise prints an error statement
* 
* Input:
* Login credentials
*
* Output:
* loggedIn = true if successful; prints error message if not successful
*/
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

/**
* Description:
* This fucntion is the prompt for the user sign up, if successful,
* it will make loggedIn true, and save into the text file; 
*
* Input:
* New user credentials
*
* Output:
* loggedIn= true and svaed into text file
*/
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


/**
* Description:
* Simple print function that prints the delete and edit option
*
* Input:
* None
*
* Output:
* Printed statement
*/
void deleteAndEditOption() {
    cout << "[1] Edit/Delete Post" << endl;
    cout << "[2] Back to browse" << endl;
    cout << "Enter option: ";
}


/**
* Description:
* Prints out Posts that was specified with by the List<Post> class input. It goes through two lists, one to check for sticky posts and one for normal posts that are not sticky
*
* Input:
* list length - to know where the for loop will stop traversing at
* list of post - to print and traverse through
* count - to count the amount of user posts there are
* 
* Output:
* Printed statement
*/
void printSticky(int currentListLength, List<Post> currentList, int& count) {
    for (int x = 0; x < currentListLength; x++) {
        if ( currentList.get(x).getSticky()) {
            count++;
            cout << "Post " << x + 1 << endl;
            printPost(currentList.get(x));
        }
    }
    for (int i = 0; i < currentListLength; i++) {
        if ( currentList.get(i).getSticky() == false) {
            count++;
            cout << "Post " << i + 1 << endl;
            printPost(currentList.get(i));
        }
    }
}

void printStickyByUser(int currentListLength, List<Post> currentList, int& count) {
    for (int x = 0; x < currentListLength; x++) {
        if (currentList.get(x).getUser() == currentUser.getName() && currentList.get(x).getSticky()) {
            count++;
            cout << "Post " << x + 1 << endl;
            printPost(currentList.get(x));
        }
    }
    for (int i = 0; i < currentListLength; i++) {
        if (currentList.get(i).getUser() == currentUser.getName() && currentList.get(i).getSticky() == false) {
            count++;
            cout << "Post " << i + 1 << endl;
            printPost(currentList.get(i));
        }
    }
}
