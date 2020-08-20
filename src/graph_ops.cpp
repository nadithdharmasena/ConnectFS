#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/graph_ops.h"
#include "../headers/existence_ops.h"
#include "../headers/file_name_ops.h"
#include "../headers/copy_ops.h"
#include "../headers/utilities.h"
#include "../headers/load_ops.h"

using namespace std;

/**
 * @description Traverse connected topics and files
 * @param node Current node in the traversal
 * @param file_map Mapping of files to their locations
 * @param destination Destination folder to which files are copied
 */
void makeExplore (const shared_ptr<Node> &node, FileMap &file_map,
                  unordered_set<string> &visited, const string &destination) {

    if (visited.find(node->getID()) != visited.end())
        return;
    else
        visited.insert(node->getID());

    if (node->isFile()) {

        string file_name, file_location, complete_name, copy_command;

        file_name = node->getName();
        file_location = file_map[file_name];
        complete_name = file_name + getFileExtension(file_location);

        file_location = "$HOME" + file_location.substr(1);

        copy_command = "cp " + file_location + " " + destination + "/" + complete_name;

        appendCopy(copy_command);

    } else {

        set<shared_ptr<Node>> children = node->getChildren();
        for (const auto & itr : children) {
            makeExplore(itr, file_map, visited, destination);
        }

    }

}

/**
 * @description List files under given node
 * @param node Node representing a Topic or File
 * @param file_map Structure that maps file name to its disk location
 */
void listExplore (const shared_ptr<Node> &node, FileMap &file_map,
                  unordered_set<string> &visited) {

    if (visited.find(node->getID()) != visited.end())
        return;
    else
        visited.insert(node->getID());

    if (node->isFile()) {

        string name = node->getName();
        cout << "(F) " << name << getFileExtension(file_map[name]) << ": " << file_map[name] << endl;

    } else {

        cout << "(T) " << node->getName() << endl;

        set<shared_ptr<Node>> children = node->getChildren();
        for (const auto & itr : children) {
            listExplore(itr, file_map, visited);
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
    child = tokens[2];
    parent = tokens[3];

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

    string file_name = getEntityFileName(op_user, "Graph");
    string edge = parent + "_Topic," + child + "_" + child_type;

    // Ensure edge-to-add is not a duplicate of an existing edge
    if (doesEdgeExist(file_name, edge)) {
        cout << "ERROR: You have attempted to add an edge that already exists." << endl;
    } else {

        string user_friendly_edge_name = parent + "->" + child;

        string message = "Are you sure you want to add new link " + user_friendly_edge_name;

        // Get confirmation from user for edge addition
        if (getConfirmation(message)) {

            ofstream graph;
            graph.open(file_name, ofstream::app);
            graph << edge << endl;
            graph.close();

            cout << "Added connection from Topic " << parent << " to " << child_type << " " << child << "." << endl;

        }

    }

}

void removeEdges (const string &entity_name, const string &entity_type, const string &op_user) {

    string entity_id = entity_name + "_" + entity_type;
    string graph_file = getEntityFileName(op_user, "Graph");

    ifstream graph_in(graph_file);
    string edge;
    stringstream updated_graph;

    while (getline(graph_in, edge)) {

        vector<string> parties;
        extractEdgeInfo(edge, parties);

        if (entity_id != parties[0] && entity_id != parties[1])
            updated_graph << edge << endl;

    }

    ofstream graph_out(graph_file, ofstream::trunc);
    graph_out << updated_graph.rdbuf();

}
