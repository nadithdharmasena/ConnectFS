
#ifndef CONNECTFS_EXISTENCE_OPS_H
#define CONNECTFS_EXISTENCE_OPS_H

#include <string>

bool doesUserExist (const std::string &possible_user, const std::string &op_user);
bool doesTopicExist (const std::string &possible_topic, const std::string &op_user);
bool doesFileExist (const std::string &possible_file, const std::string &op_user);

bool doesEdgeExist (const std::string &file_name, const std::string &edge);

#endif //CONNECTFS_EXISTENCE_OPS_H
