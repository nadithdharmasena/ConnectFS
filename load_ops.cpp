#include <iostream>
#include <fstream>

#include "load_ops.h"
#include "file_name_ops.h"

using namespace std;

/**
 * @description Generate mapping from file name to its disk location
 * @param op_user Name of operating user
 * @param file_map Reference to structure that stores mapping
 */
void loadFileMap (const string &op_user, FileMap &file_map) {

    file_map.clear();
    string file_name = getEntityFileName(op_user, "Files");

    ifstream files(file_name);
    string file, name, location;
    int comma_pos;

    while (getline(files, file)) {

        comma_pos = file.find_first_of(',', 0);
        name = file.substr(0, comma_pos);
        location = file.substr(comma_pos + 1);

        file_map[name] = location;

    }

    files.close();

}

/**
 * @description Load the operating user's file system graph into memory
 * @param op_user Name of operating user
 * @param graph_map unordered_map which holds the graph
 */
void loadGraph (const string &op_user, Graph &graph_map) {

    graph_map.clear();

    string file_name = getEntityFileName(op_user, "Graph");

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
