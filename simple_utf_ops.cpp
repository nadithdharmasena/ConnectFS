#include <iostream>
#include <fstream>

#include "simple_utf_ops.h"
#include "utilities.h"

using namespace std;

/**
 * @description Create user, topic, or file under given operating user
 * @param tokens All items in user's input command
 * @param op_user Name of operating user
 */
void createEntity (const vector<string> &tokens, const string &op_user) {

    string entity = tokens[1];
    string name = tokens[2];
    string file;

    bool (*doesExist)(const string &, const string &);
    void (*addEntity)(const string &, const string &, const string &);

    // Assign proper validator/addition functions to doesExist and addEntity
    // Based on user's input
    if (entity == "user") {
        doesExist = &doesUserExist;
        addEntity = &addUser;
    } else if (entity == "topic") {
        doesExist = &doesTopicExist;
        addEntity = &addTopic;
    } else if (entity == "file") {

        if (tokens.size() != 4) {
            displayHelp(tokens[0]);
            return;
        } else {
            file = tokens[3];
        }

        doesExist = &doesFileExist;
        addEntity = &addFile;
    }

    bool is_name_alpha, does_exist;
    entity[0] = toupper(entity[0]);

    // Checks if topic or file name adheres to naming conventions and is not a duplicate
    if (name.size() >= 3 && (is_name_alpha = isNameAlphaNum(name)) && !(does_exist = doesExist(name, op_user)) ) {

        bool confirmed = getConfirmation(entity, name);

        if (confirmed) {
            addEntity(name, op_user, file);
        } else {
            cout << entity << " " << name << " was not added." << endl;
        }

    } else {

        // Determines and notifies the user of the triggered error
        if (name.size() < 3) {
            cout << entity << " name has to be at least 3 characters long." << endl;
        } else if (!is_name_alpha) {
            cout << entity << " name can only contain alphabetic characters." << endl;
        } else if (does_exist) {
            cout << entity << " " << name << " already exists." << endl;
        }

    }


}

/**
 * @description Determine whether the user exists
 * @param possible_user Name of user in question
 * @param op_user Name of operating user
 * @return True if user exists; false if not
 */
bool doesUserExist (const string &possible_user, const string &op_user) {

    ifstream users("./data/Users");
    string real_user;

    while (users >> real_user) {
        if (real_user == possible_user) {
            users.close();
            return true;
        }
    }

    users.close();
    return false;

}

/**
 * @description Determine whether the topic exists under the given operating user
 * @param possible_topic Name of topic in question
 * @param op_user Name of operating user
 * @return True if topic exists; false if not
 */
bool doesTopicExist (const string &possible_topic, const string &op_user) {

    string file_name = makeFileName(op_user, "Topics");

    ifstream topics(file_name);
    string real_topic;

    while (topics >> real_topic) {
        if (real_topic == possible_topic) {
            topics.close();
            return true;
        }
    }

    topics.close();
    return false;
}

/**
 * @description Determine whether the file exists under the given operating user
 * @param possible_file Name of file in question
 * @param op_user Name of operating user
 * @return True if file exists; false if not
 */
bool doesFileExist (const string &possible_file, const string &op_user) {

    string file_name = makeFileName(op_user, "Files");

    ifstream files(file_name);
    string old_file, old_file_name;
    size_t comma_pos;

    while (getline(files, old_file)) {

        comma_pos = old_file.find_first_of(',', 0);
        old_file_name = old_file.substr(0, comma_pos);

        if (old_file_name == possible_file)
            return true;

    }

    files.close();
    return false;

}

/**
 * @description Add new user
 * @param new_user Name of user to be added
 * @param op_user Unused argument; exists to maximize code reuse in createEntity()
 * @param extra Unused argument; exists to maximize code reuse in createEntity()
 */
void addUser (const string &new_user, const string &op_user, const string &extra) {

    string file_name = data_path + "Users";

    ofstream users;
    users.open(file_name, ofstream::app);
    users << new_user << endl;
    users.close();

    cout << "Added User " << new_user << "." << endl;

}

/**
 * @description Add new topic for given user with given name
 * @param new_topic Name of topic to be added
 * @param op_user Name of operating user under which topic will be added
 * @param extra Unused argument; exists to maximize code reuse in createEntity()
 */
void addTopic (const string &new_topic, const string &op_user, const string &extra) {

    string file_name = makeFileName(op_user, "Topics");

    ofstream topics;
    topics.open(file_name, ofstream::app);
    topics << new_topic << endl;
    topics.close();

    cout << "Added Topic " << new_topic << " for " << op_user << "." << endl;

}

/**
 * @description Add new file for given user with given name, location
 * @param new_file Name of file to be added
 * @param op_user Name of operating user under which file will be added
 * @param file_path Location of file
 */
void addFile (const string &new_file, const string &op_user, const string &file_path) {

    if (file_path.empty()) {
        cout << "File " << new_file << " was not added because it pointed to nothing." << endl;
        return;
    }

    string file_name = makeFileName(op_user, "Files");
    string added_file = new_file + "," + file_path;

    ofstream files;
    files.open(file_name, ofstream::app);
    files << added_file << endl;
    files.close();

    cout << "Added File " << new_file << "[" << file_path << "] for " << op_user << "." << endl;

}

/**
 * @description Show list of users
 */
void showUsers () {

    ifstream users("./data/Users");

    string real_user;
    while (users >> real_user) {
        cout << real_user << endl;
    }

    users.close();

}

/**
 * @description Show list of topics under given operating user
 * @param op_user Name of operating user
 */
void showTopics (const string &op_user) {

    string file_name = makeFileName(op_user, "Topics");


    ifstream topics(file_name);
    string real_topic;

    while (topics >> real_topic) {
        cout << real_topic << endl;
    }

    topics.close();

}

/**
 * @description Show list of files under given operating user
 * @param op_user Name of operating user
 */
void showFiles (const string &op_user) {

    string file_name = makeFileName(op_user, "Files");

    ifstream files(file_name);
    string file, name, location;
    size_t comma_pos;

    while (getline(files, file)) {

        comma_pos = file.find_first_of(',', 0);
        name = file.substr(0, comma_pos);
        location = file.substr(comma_pos + 1);

        cout << name << ": " << location << endl;

    }

    files.close();

}

/**
 * @description Generate mapping from file name to its disk location
 * @param op_user Name of operating user
 * @param file_map Reference to structure that stores mapping
 */
void loadFileMap (const string &op_user, FileMap &file_map) {

    file_map.clear();
    string file_name = makeFileName(op_user, "Files");

    ifstream files(file_name);
    string file, name, location;
    size_t comma_pos;

    while (getline(files, file)) {

        comma_pos = file.find_first_of(',', 0);
        name = file.substr(0, comma_pos);
        location = file.substr(comma_pos + 1);

        file_map[name] = location;

    }

    files.close();

}

string getFileExtension (const string &file_loc) {

    int pos = file_loc.find_last_of('.');
    return file_loc.substr(pos);

}

/**
 * @description Generate file name for operating user and entity type to access
 * @param op_user Name of operating user
 * @param type Entity type to access
 * @return File name to access
 */
string makeFileName (const string &op_user, const string &type) {

    string file_name = data_path + op_user + "_" + type;
    return file_name;

}