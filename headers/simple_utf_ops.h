
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

void addUser (const std::string &new_user, const std::string &op_user, const std::string &extra);
void addTopic (const std::string &new_topic, const std::string &op_user, const std::string &extra);
void addFile (const std::string &new_file, const std::string &op_user, const std::string &file_path);

void showUsers ();
void showTopics (const std::string &op_user);
void showFiles (const std::string &op_user);

void removeUser (const std::string &user_to_remove, const std::string &op_user);
void removeTopic (const std::string &topic_to_remove, const std::string &op_user);
void removeFile (const std::string &topic_to_remove, const std::string &op_user);

#endif //CONNECTFS_SIMPLE_UTF_OPS_H
