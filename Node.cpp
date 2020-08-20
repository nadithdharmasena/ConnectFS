#include <iostream>

#include "Node.h"

using namespace std;

/**
 * @description Initializes name, id, and file status
 * @param node_id Party ID extracted from edge ID
 */
Node::Node (const string& node_id) {

    int us_pos = node_id.find_first_of('_', 0);

    string name = node_id.substr(0, us_pos);
    string suffix = node_id.substr(us_pos + 1);

    if (suffix == "File")
        this->is_file = true;
    else
        this->is_file = false;

    this->name = name;
    this->node_id = node_id;

}

/**
 * @description Used for lexicographical sorting of child pointers by node name
 * @param right Right side of < operator
 * @return True if current node is less than right node
 */
bool Node::operator< (const shared_ptr<Node> &right) {
    return name < right->getName();
}

/**
 * @description Adds given node as a child of "this" node
 * @param child Pointer to child node
 */
void Node::addChild (const shared_ptr<Node> &child) {
    children.insert(child);
}

bool Node::isFile () {
    return is_file;
}

set<shared_ptr<Node>>& Node::getChildren () {
    return children;
}

string& Node::getID () {
    return node_id;
}

string& Node::getName() {
    return name;
}
