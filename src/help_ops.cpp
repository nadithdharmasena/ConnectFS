#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../headers/help_ops.h"

using namespace std;

static string help_file_location = "./misc/help";

/**
 * @description Display in-depth explanation of given command
 * @param command User's command
 */
void printHelp (const string &command) {

    ifstream help_in(help_file_location);
    string line;
    stringstream help_out;

    bool collect = false;

    while (getline(help_in, line)) {

        if (line == command && collect) {
            break;
        } else if (line == command) {
            collect = true;
        } else if (collect) {
            help_out << line << endl;
        }

    }

    cout << help_out.rdbuf();

}


/**
 * @description Display help prompt for given command
 * @param command Holds type of command
 */
void displayHelp (const string &command) {
    cout << "Use the following command to get help." << endl;
    cout << "\t" << command << " help" << endl;
}