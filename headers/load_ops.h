
#ifndef CONNECTFS_LOAD_OPS_H
#define CONNECTFS_LOAD_OPS_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "Node.h"

typedef std::unordered_map<std::string, std::shared_ptr<Node>> Graph;
typedef std::unordered_map<std::string, std::string> FileMap;

void loadFileMap (const std::string &op_user, FileMap &file_map);
void loadGraph (const std::string &op_user, Graph &graph_map);

void extractEdgeInfo (const std::string &edge, std::vector<std::string> &parties);

#endif //CONNECTFS_LOAD_OPS_H
