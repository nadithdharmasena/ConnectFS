
#include "../headers/file_name_ops.h"

using namespace std;

/**
 * @description Generate file name for operating user and entity type to access
 * @param op_user Name of operating user
 * @param type Entity type to access
 * @return File name to access
 */
string getEntityFileName (const string &op_user, const string &type) {

    string file_name = data_path + op_user + "_" + type;
    return file_name;

}

/**
 * @description Generates file name for bash file for folder creation
 * @return
 */
string getMakeFileName () {
    return data_path + "make_file.sh";
}

/**
 * @description Find file extension given its location
 * @param file_loc Location of file
 * @return Extension of file
 */
string getFileExtension (const string &file_loc) {
    int pos = file_loc.find_last_of('.');
    return file_loc.substr(pos);
}