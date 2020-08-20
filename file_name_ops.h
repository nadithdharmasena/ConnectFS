
#ifndef CONNECTFS_FILE_NAME_OPS_H
#define CONNECTFS_FILE_NAME_OPS_H

#include <string>

extern std::string data_path;

std::string getEntityFileName (const std::string &op_user, const std::string &type);
std::string getMakeFileName ();

std::string getFileExtension (const std::string &file_loc);

#endif //CONNECTFS_FILE_NAME_OPS_H
