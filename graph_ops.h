
#ifndef CONNECTFS_GRAPH_OPS_H
#define CONNECTFS_GRAPH_OPS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Node.h"

typedef std::unordered_map<std::string, std::shared_ptr<Node>> Graph;
typedef std::unordered_map<std::string, std::string> FileMap;

void createMakeFile ();
void executeMakeFile (const std::string &destination);
void deleteMakeFile ();

void makeExplore (const std::shared_ptr<Node> &node, FileMap &file_map,
                  std::unordered_set<std::string> &visited, const std::string &destination);

void listExplore (const std::shared_ptr<Node> &node, FileMap &file_map,
                  std::unordered_set<std::string> &visited);

void addEdge (const std::vector<std::string> &tokens, const std::string &op_user);

void removeEdges (const std::string &entity_name, const std::string &entity_type, const std::string &op_user);

#endif //CONNECTFS_GRAPH_OPS_H
