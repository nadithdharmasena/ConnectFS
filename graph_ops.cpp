#include <iostream>
#include <fstream>

using namespace std;

bool doesEdgeExist (const string &file_name, const string &edge);

/**
 * @description Adds edge between a topic and topic or topic and file
 * @remark Checks for edge parties exist and edge-to-add is not a duplicate
 * @param tokens Tokens of user's input
 * @param op_user Name of operating user
 */
void addEdge (const vector<string> &tokens, const string &op_user) {

    string child_type, parent, child;
    bool (*doesExist)(const string &, const string &);

    child_type = tokens[1];
    parent = tokens[2];
    child = tokens[3];

    // Point validation function to topic or file validator based on user input
    doesExist = child_type == "topic" ? &doesTopicExist : &doesFileExist;

    // Capitalize child type for aesthetic purposes
    child_type[0] = toupper(child_type[0]);

    // Ensure that both parties of edge exist
    if (!doesTopicExist(parent, op_user)) {
        cout << "Topic " << parent << " does not exist. Use the following command to create it." << endl;
        cout << "\tcreate topic " << parent << endl;
        return;
    } else if (!doesExist(child, op_user)) {
        cout << child_type << " " << child << " does not exist. Use the following command to create it." << endl;
        cout << "\tcreate " << child_type << " " << child << " <location>" << endl;
        return;
    }

    string file_name = data_path + op_user + "_Graph";
    string edge = parent + "_Topic," + child + "_" + child_type;

    // Ensure edge-to-add is not a duplicate of an existing edge
    if (doesEdgeExist(file_name, edge)) {
        cout << "ERROR: You have attempted to add an edge that already exists." << endl;
    } else {

        string user_friendly_edge_name = parent + "->" + child;

        // Get confirmation from user for edge addition
        if (getConfirmation("connection", user_friendly_edge_name)) {

            ofstream graph;
            graph.open(file_name, ofstream::app);
            graph << edge << endl;
            graph.close();

            cout << "Added connection from Topic " << parent << " to " << child_type << " " << child << "." << endl;

        } else {
            cout << user_friendly_edge_name << " was not added." << endl;
        }

    }

}

/**
 * @description Determines whether the given edge exists in given file
 * @param file_name Name of file at which edge could exist
 * @param edge Name of edge
 * @return True if edge exists, false if not
 */
bool doesEdgeExist (const string &file_name, const string &edge) {

    ifstream graph(file_name);
    string real_edge;

    // Check each edge record for match; return true if match found
    while (getline(graph, real_edge)) {
        if (real_edge == edge) {
            graph.close();
            return true;
        }
    }

    graph.close();
    return false;

}