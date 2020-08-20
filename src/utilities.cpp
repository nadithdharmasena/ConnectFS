#include <iostream>

#include "../headers/utilities.h"

using namespace std;

/**
 * @description Tokenizes the user's shell input by space
 * @param input User's shell input
 * @param tokens Holds tokenized values
 */
void tokenizeInput (const string &input, vector<string> &tokens) {

    // Leave the tokens vector empty if the user input nothing
    if (input.empty())
        return;

    int pos, prev_pos = 0;
    pos = input.find_first_of(' ', prev_pos);

    while (true) {

        string token;

        if (pos == -1) {
            token = input.substr(prev_pos);
            if (!token.empty())
                tokens.push_back(token);
            break;
        } else {
            token = input.substr(prev_pos, pos - prev_pos);
            tokens.push_back(token);

            prev_pos = pos + 1;
            if (prev_pos < input.size() - 1 && input[prev_pos] == '"') {
                prev_pos++;
                pos = input.find_first_of('"', prev_pos);
            } else {
                pos = input.find_first_of(' ', prev_pos);
            }

        }
    }

}

/**
 * @description Determines if name only contains alphabetic characters
 * @param name
 * @return True if all characters are alphabetic; false if not
 */
bool isNameAlphaNum (const string &name) {

    for (char letter : name) {
        if (!isalnum(letter))
            return false;
    }

    return true;

}

/**
 * @description Asks user for confirmation on adding a new UTF
 * @param message Either User, Topic, or File
 * @param name Name of entity to be added
 * @return True if user confirmed addition, false if not
 */
bool getConfirmation (const string &message) {

    cout << message << " (Y/N)? ";

    string response;
    getline(cin, response);

    if (response == "Y")
        return true;
    else
        return false;

}

/**
 * @description Display help prompt for given command
 * @param command Holds type of command
 */
void displayHelp (const string &command) {
    cout << "Use the following command to get help." << endl;
    cout << "\t" << command << " help" << endl;
}