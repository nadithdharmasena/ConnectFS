#include <iostream>
#include <fstream>
#include <unistd.h>

#include "../headers/copy_ops.h"
#include "../headers/file_name_ops.h"

using namespace std;

/**
 * @description Creates and sets permissions for the file copy bash script
 */
void createMakeFile () {

    string file_name = getMakeFileName();

    ofstream make_file(file_name);
    make_file << "#!/bin/bash" << endl;
    make_file.close();

    if (fork() == 0) {
        int ret_val = execlp("/bin/chmod", "chmod", "+x", file_name.c_str(), nullptr);
        cout << ret_val << endl;
    } else {
        wait(nullptr);
    }

}

/**
 * @description Appends command to file copy bash script
 * @param command Command to append
 */
void appendCopy (const string &command) {

    string file_name = getMakeFileName();

    ofstream make_file;
    make_file.open(file_name, ofstream::app);
    make_file << command << endl;
    make_file.close();

}

/**
 * @description Executes the folder creation make file
 * @param destination Location of destination folder
 */
void executeMakeFile (const string &destination) {

    string file_name = getMakeFileName();

    ofstream make_file;

    make_file.open(file_name, ofstream::app);
    make_file << "open " << destination << endl;
    make_file.close();

    string command = "./" + file_name;

    if (fork() == 0) {
        execlp(command.c_str(), nullptr);
    } else {
        wait(nullptr);
    }

}

/**
 * @description Deletes the file copy bash script
 */
void deleteMakeFile () {

    string file_name = getMakeFileName();

    if (fork() == 0) {
        execlp("/bin/rm", "rm", file_name.c_str(),nullptr);
    } else {
        wait(nullptr);
    }

}
