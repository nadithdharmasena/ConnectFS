#include <iostream>
#include <fstream>
#include <memory>

#include "Node.h"

using namespace std;

typedef unordered_map<string, shared_ptr<Node>> Graph;
typedef unordered_map<string, string> FileMap;

void listExplore (const shared_ptr<Node> &node, FileMap &file_map);
void addEdge (const vector<string> &tokens, const string &op_user);
void loadGraph (const string &op_user, Graph &graph_map);
void extractEdgeInfo (const string &edge, vector<string> &parties);
bool doesEdgeExist (const string &file_name, const string &edge);
string makeGraphFileName (const string &op_user);

/**
 * @description List files under given node
 * @param node Node representing a Topic or File
 * @param file_map Structure that maps file name to its disk location
 */
void listExplore (const shared_ptr<Node> &node, FileMap &file_map) {

    if (node->isFile()) {
        string name = node->getName();
        cout << name << ": " << file_map[name] << endl;
    } else {

        set<shared_ptr<Node>> children = node->getChildren();
        for (auto itr = children.begin(); itr != children.end(); ++itr) {
            listExplore(*itr, file_map);
        }

    }

}

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

    string file_name = makeGraphFileName(op_user);
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
 * @description Load the operating user's file system graph into memory
 * @param op_user Name of operating user
 * @param graph_map unordered_map which holds the graph
 */
void loadGraph (const string &op_user, Graph &graph_map) {

    string file_name = makeGraphFileName(op_user);

    ifstream graph(file_name);
    string edge;

    while (getline(graph, edge)) {

        vector<string> edge_info;
        extractEdgeInfo(edge, edge_info);

        string parent = edge_info[0];
        string child = edge_info[1];

        if (graph_map.find(parent) == graph_map.end())
            graph_map[parent] = make_shared<Node>(parent);

        if (graph_map.find(child) == graph_map.end())
            graph_map[child] = make_shared<Node>(child);

        graph_map[parent]->addChild(graph_map[child]);

    }

}

/**
 * @description Extract party IDs from edge ID
 * @param edge Edge ID
 * @param parties Reference to vector that holds the edge's party IDs
 */
void extractEdgeInfo (const string &edge, vector<string> &parties) {

    int comma_pos = edge.find_first_of(',', 0);

    string parent_id = edge.substr(0, comma_pos);
    string child_id = edge.substr(comma_pos + 1);

    parties.push_back(parent_id);
    parties.push_back(child_id);

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

/**
 * @description Generates file name for given operating user's graph
 * @param op_user Name of operating user
 * @return File name of operating user's graph
 */
string makeGraphFileName (const string &op_user) {
    string file_name = data_path + op_user + "_Graph";
    return file_name;
}