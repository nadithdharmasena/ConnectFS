
#ifndef CONNECTFS_GRAPH_OPS_H
#define CONNECTFS_GRAPH_OPS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "Node.h"

typedef std::unordered_map<std::string, std::shared_ptr<Node>> Graph;
typedef std::unordered_map<std::string, std::string> FileMap;

extern std::string data_path;

void createMakeFile ();
void appendCommand (const std::string &command);
void executeMakeFile (const std::string &destination);
void deleteMakeFile ();

void makeExplore (const std::shared_ptr<Node> &node, FileMap &file_map, std::string destination);
void listExplore (const std::shared_ptr<Node> &node, FileMap &file_map);
void addEdge (const std::vector<std::string> &tokens, const std::string &op_user);
void loadGraph (const std::string &op_user, Graph &graph_map);
void extractEdgeInfo (const std::string &edge, std::vector<std::string> &parties);
bool doesEdgeExist (const std::string &file_name, const std::string &edge);

static std::string getGraphFileName (const std::string &op_user);
static std::string getMakeFileName ();

#endif //CONNECTFS_GRAPH_OPS_H
