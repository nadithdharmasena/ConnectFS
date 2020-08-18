#include <string>
#include <set>
#include <memory>

using namespace std;

#ifndef CONNECTFS_NODE_H
#define CONNECTFS_NODE_H

class Node {
private:
    string node_id, name;
    bool is_file;
    set<shared_ptr<Node>> children;
public:
    explicit Node (const string& node_id);
    bool operator< (const shared_ptr<Node> &right);

    void addChild (const shared_ptr<Node> &child);
    bool isFile();
    set<shared_ptr<Node>>& getChildren ();
    string& getID ();
    string& getName();
};

#endif //CONNECTFS_NODE_H
