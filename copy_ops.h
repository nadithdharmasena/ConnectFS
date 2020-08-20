//
// Created by Nadith Dharmasena on 8/20/20.
//

#ifndef CONNECTFS_COPY_OPS_H
#define CONNECTFS_COPY_OPS_H

#include <string>

void createMakeFile ();
void appendCopy (const std::string &command);
void executeMakeFile (const std::string &destination);
void deleteMakeFile ();

#endif //CONNECTFS_COPY_OPS_H
