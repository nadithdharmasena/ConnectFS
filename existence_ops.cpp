#include <fstream>

#include "existence_ops.h"
#include "file_name_ops.h"

using namespace std;


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

    string file_name = getEntityFileName(op_user, "Topics");

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

    string file_name = getEntityFileName(op_user, "Files");

    ifstream files(file_name);
    string old_file, old_file_name;
    int comma_pos;

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
 * @description Determines whether the given edge exists in given file
 * @param file_name Name of file at which edge could exist
 * @param edge Name of edge
 * @return True if edge exists, false if not
 */
bool doesEdgeExist (const string &file_name, const string &edge) {

    ifstream graph(file_name);
    string real_edge;

    // Check each edge record for match; return true if match found
    while (getline(graph, real_edge)) {
        if (real_edge == edge) {
            graph.close();
            return true;
        }
    }

    graph.close();
    return false;

}
