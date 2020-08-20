#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/simple_utf_ops.h"
#include "../headers/graph_ops.h"
#include "../headers/utilities.h"
#include "../headers/existence_ops.h"
#include "../headers/file_name_ops.h"

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

        string message = "Are you sure you want to add new " + entity + " " + name;

        bool confirmed = getConfirmation(message);

        if (confirmed) {
            addEntity(name, op_user, file);
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

    string file_name = getEntityFileName(op_user, "Topics");

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

    string file_name = getEntityFileName(op_user, "Files");
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

    string file_name = getEntityFileName(op_user, "Topics");


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

    string file_name = getEntityFileName(op_user, "Files");

    ifstream files(file_name);
    string file, name, location;
    int comma_pos;

    while (getline(files, file)) {

        comma_pos = file.find_first_of(',', 0);
        name = file.substr(0, comma_pos);
        location = file.substr(comma_pos + 1);

        cout << name << ": " << location << endl;

    }

    files.close();

}

/**
 * @description Remove user record from Users file
 * @param user_to_remove Name of user to remove
 * @param op_user Name of operating user
 */
void removeUser (const string &user_to_remove, const string &op_user) {

    if (user_to_remove == op_user) {
        cout << "You cannot delete the current user." << endl;
    } else {

        string users_file = data_path + "Users";

        ifstream users_in(users_file);
        string user;
        stringstream updated_users;

        while (getline(users_in, user)) {
            if (user != user_to_remove)
                updated_users << user << endl;
        }

        ofstream users_out(users_file, ofstream::trunc);
        users_out << updated_users.rdbuf();

    }

}

void removeTopic (const string &topic_to_remove, const string &op_user) {

    string topics_file = getEntityFileName(op_user, "Topics");

    ifstream topics_in(topics_file);
    string topic;
    stringstream updated_topics;

    // Keeping topics that are not the topic to be removed
    while (getline(topics_in, topic)) {
        if (topic != topic_to_remove)
            updated_topics << topic << endl;
    }

    ofstream topics_out(topics_file, ofstream::trunc);
    topics_out << updated_topics.rdbuf();

    removeEdges(topic_to_remove, "Topic", op_user);

}

void removeFile (const string &file_to_remove, const string &op_user) {

    string files_file = getEntityFileName(op_user, "Files");

    ifstream files_in(files_file);
    string file, name;
    int comma_pos;
    stringstream updated_files;

    while (getline(files_in, file)) {

        comma_pos = file.find_first_of(',', 0);
        name = file.substr(0, comma_pos);

        if (name != file_to_remove)
            updated_files << file << endl;

    }

    ofstream files_out(files_file, ofstream::trunc);
    files_out << updated_files.rdbuf();

    removeEdges(file_to_remove, "File", op_user);

}