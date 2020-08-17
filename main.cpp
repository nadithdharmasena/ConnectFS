#include <iostream>
#include <vector>
#include <unordered_set>
#include <unistd.h>

#include "utilities.cpp"
#include "simple_utf_ops.cpp"
#include "graph_ops.cpp"

using namespace std;

unordered_set<string> entities{"user", "topic", "file"};
string data_path = "./data/";

void handleUse (const vector<string> &tokens, string &op_user);
void handleCreate (const vector<string> &tokens, const string &op_user);
void handleShow (const vector<string> &tokens, const string &op_user);
void handleAdd (const vector<string> &tokens, const string &op_user);

int main(int ac, char **argv) {

    string op_user = "Default", input;
    bool display_shell = true;

    while (display_shell) {
        cout << "ConnectFS> ";

        getline(cin, input);

        vector<string> tokens;
        tokenizeInput(input, tokens);

        if (tokens.empty()) {
            continue;
        } else if (tokens[0] == "exit") {
            // User entered exit to quit the shell
            display_shell = false;
        } else if (tokens[0] == "who") {
            // User entered "Who am I?" command to determine
            // Under which user they are currently operating
            cout << "The current operating user is " << op_user << "." << endl;
        } else if (tokens[0] == "use") {
            // User entered "Use User" command
            handleUse(tokens, op_user);
        } else if (tokens[0] == "create") {
            // User entered "Create" command to create new user, topic, or file
            handleCreate(tokens, op_user);
        } else if (tokens[0] == "show") {
            // User entered "See" command to see list of
            // Users, topics, or files
            handleShow(tokens, op_user);
        } else if (tokens[0] == "add") {
            // User entered "Add" command to add a File/Topic under a Topic
            // Ensure user does not add a cycle in the graph?
            handleAdd(tokens, op_user);
        }

    }

    return 0;

}

void handleUse (const vector<string> &tokens, string &op_user) {

    if (tokens.size() != 2) {
        displayHelp(tokens[0]);
    } else if (tokens[1] == "help") {
        cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
    } else {

        string new_user = tokens[1];

        // Checks for existence of user
        if (doesUserExist(new_user, op_user)) {
            op_user = new_user;
            cout << "Operating user switched to " << new_user << "." << endl;
        } else {
            cout << "User " << new_user << " does not exist. Use the following command to create it." << endl;
            cout << "\tcreate user " << new_user << endl;
        }

    }

}

void handleCreate (const vector<string> &tokens, const string &op_user) {

    if (tokens.size() < 3) {

        if (tokens.size() == 2 && tokens[1] == "help") {
            cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
        } else {
            displayHelp(tokens[0]);
        }

    } else if (entities.find(tokens[1]) != entities.end()) {
        createEntity(tokens, op_user);
    } else {
        displayHelp(tokens[0]);
    }

}

void handleShow (const vector<string> &tokens, const string &op_user) {

    if (tokens.size() < 2) {
        displayHelp(tokens[0]);
    } else if (tokens[1] == "users") {
        showUsers();
    } else if (tokens[1] == "topics") {
        showTopics(op_user);
    } else if (tokens[1] == "files") {
        showFiles(op_user);
    } else if (tokens[1] == "path") {
        cout << "Path" << endl;
    } else if (tokens[1] == "help") {
        cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
    } else {
        displayHelp(tokens[0]);
    }

}

void handleAdd (const vector<string> &tokens, const string &op_user) {

    if (tokens.size() != 4) {

        if (tokens.size() == 2 && tokens[1] == "help") {
            cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
        } else {
            displayHelp(tokens[0]);
        }

    } else if (tokens[1] == "topic" || tokens[1] == "file") {
        addEdge(tokens, op_user);
    } else {
        displayHelp(tokens[0]);
    }

}