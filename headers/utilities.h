
#ifndef CONNECTFS_UTILITIES_H
#define CONNECTFS_UTILITIES_H

#include <string>
#include <vector>

extern std::string data_path;

void tokenizeInput (const std::string &input, std::vector<std::string> &tokens);
bool isNameAlphaNum (const std::string &name);
bool getConfirmation (const std::string &message);
void displayHelp (const std::string &command);

#endif //CONNECTFS_UTILITIES_H
