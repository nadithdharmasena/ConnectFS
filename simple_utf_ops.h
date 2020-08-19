
#ifndef CONNECTFS_SIMPLE_UTF_OPS_H
#define CONNECTFS_SIMPLE_UTF_OPS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "Node.h"

typedef std::unordered_map<std::string, std::shared_ptr<Node>> Graph;
typedef std::unordered_map<std::string, std::string> FileMap;

extern std::string data_path;

void createEntity (const std::vector<std::string> &tokens, const std::string &op_user);

bool doesUserExist (const std::string &possible_user, const std::string &op_user);
bool doesTopicExist (const std::string &possible_topic, const std::string &op_user);
bool doesFileExist (const std::string &possible_file, const std::string &op_user);

void addUser (const std::string &new_user, const std::string &op_user, const std::string &extra);
void addTopic (const std::string &new_topic, const std::string &op_user, const std::string &extra);
void addFile (const std::string &new_file, const std::string &op_user, const std::string &file_path);

void showUsers ();
void showTopics (const std::string &op_user);
void showFiles (const std::string &op_user);

void loadFileMap (const std::string &op_user, FileMap &file_map);
std::string getFileExtension (const std::string &file_loc);
std::string makeFileName (const std::string &op_user, const std::string &type);

#endif //CONNECTFS_SIMPLE_UTF_OPS_H
