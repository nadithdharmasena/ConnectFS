#include <iostream>
#include <unordered_set>

#include "utilities.h"
#include "simple_utf_ops.h"
#include "graph_ops.h"

using namespace std;

string data_path = "./data/";

void handleUse (const vector<string> &tokens, string &op_user, Graph &graph_map, FileMap &file_map);
void handleCreate (const vector<string> &tokens, const string &op_user);
void handleShow (const vector<string> &tokens, const string &op_user);
void handleLink (const vector<string> &tokens, const string &op_user);
void handleList (const vector<string> &tokens, Graph &graph_map, FileMap &file_map);
void handleMake (const vector<string> &tokens, Graph &graph_map, FileMap &file_map);

int main(int ac, char **argv) {

    string op_user = "Default", input;

    Graph graph_map;
    FileMap file_map;

    bool display_shell = true;
    bool reload_graph = true;

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
            handleUse(tokens, op_user, graph_map, file_map);
            reload_graph = false;
        } else if (tokens[0] == "create") {
            // User entered "Create" command to create new user, topic, or file
            handleCreate(tokens, op_user);
        } else if (tokens[0] == "show") {
            // User entered "See" command to see list of
            // Users, topics, or files
            handleShow(tokens, op_user);
        } else if (tokens[0] == "link") {
            // User entered "Link" command to link a File/Topic to a Topic
            handleLink(tokens, op_user);
            reload_graph = true;
        } else if (tokens[0] == "list" || tokens[0] == "make") {

            if (reload_graph) {
                loadGraph(op_user, graph_map);
                loadFileMap(op_user, file_map);
                reload_graph = false;
            }

            if (tokens[0] == "list")
                handleList(tokens, graph_map, file_map);
            else
                handleMake(tokens, graph_map, file_map);

        } else {
            cout << "Type help." << endl;
        }

    }

    return 0;

}

/**
 * @description Handle the use command; change the operating user
 * @param tokens Tokenized user input
 * @param op_user Reference to main's operating user string
 * @param graph_map Reference to main's graph structure
 * @param file_map Reference to main's file to location structure
 */
void handleUse (const vector<string> &tokens, string &op_user, Graph &graph_map, FileMap &file_map) {

    if (tokens.size() != 2) {
        displayHelp(tokens[0]);
    } else if (tokens[1] == "help") {
        cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
    } else {

        string new_user = tokens[1];

        if (new_user == op_user) {
            // Checks if the user attempted to switch to the current operating user
            cout << "You are already using " << new_user << "." << endl;
        } else if (doesUserExist(new_user, op_user)) {
            // Checks for existence of user
            op_user = new_user;
            loadGraph(op_user, graph_map);
            loadFileMap(op_user, file_map);
            cout << "Operating user switched to " << new_user << "." << endl;
        } else {
            cout << "User " << new_user << " does not exist. Use the following command to create it." << endl;
            cout << "\tcreate user " << new_user << endl;
        }

    }

}

/**
 * @description Handle create command; add U,T, or F to permanent storage
 * @param tokens Tokenized user input
 * @param op_user Name of operating user
 */
void handleCreate (const vector<string> &tokens, const string &op_user) {

    unordered_set<string> entities{"user", "topic", "file"};

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

/**
 * @description Handle show command; show U,T, or F
 * @param tokens Tokenized user input
 * @param op_user Name of operating user
 */
void handleShow (const vector<string> &tokens, const string &op_user) {

    if (tokens.size() < 2) {
        displayHelp(tokens[0]);
    } else if (tokens[1] == "users") {
        showUsers();
    } else if (tokens[1] == "topics") {
        showTopics(op_user);
    } else if (tokens[1] == "files") {
        showFiles(op_user);
    } else if (tokens[1] == "help") {
        cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
    } else {
        displayHelp(tokens[0]);
    }

}

/**
 * @description Handle add command; add edge between Topic and Topic/File
 * @param tokens Tokenized user input
 * @param op_user Name of operating user
 */
void handleLink (const vector<string> &tokens, const string &op_user) {

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

/**
 * @description List the files and topics connected to a topic
 * @param tokens Tokenized user input
 * @param graph_map Structure containing topic-file graph
 * @param file_map Mapping of file names to their locations
 */
void handleList (const vector<string> &tokens, Graph &graph_map, FileMap &file_map) {

    if (tokens.size() == 2) {

        if (tokens[1] == "help") {
            cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
        } else {

            string topic = tokens[1] + "_Topic";

            if (graph_map.find(topic) != graph_map.end()) {
                shared_ptr<Node> topic_ptr = graph_map[topic];
                listExplore(topic_ptr, file_map);
            } else {
                cout << "Topic " << tokens[1] << " has not been added to the graph." << endl;
            }

        }

    } else {
        displayHelp(tokens[0]);
    }

}

/**
 * @description Make a folder containing the files connected to a topic
 * @param tokens Tokenized user input
 * @param graph_map Structure containing topic-file graph
 * @param file_map Mapping of file names to their locations
 */
void handleMake (const vector<string> &tokens, Graph &graph_map, FileMap &file_map) {

    if (tokens.size() == 3) {

        string topic = tokens[1] + "_Topic";

        if (graph_map.find(topic) != graph_map.end()) {

            shared_ptr<Node> topic_ptr = graph_map[topic];
            string destination = tokens[2];

            createMakeFile();
            makeExplore(topic_ptr, file_map, destination);
            executeMakeFile(destination);
            deleteMakeFile();

        } else {
            cout << "Topic " << tokens[1] << " has not been added to the graph." << endl;
        }

    } else if (tokens.size() == 2 && tokens[1] == "help") {
        cout << "Print out list of arguments and description for " << tokens[0] << "." << endl;
    } else {
        displayHelp(tokens[0]);
    }

}