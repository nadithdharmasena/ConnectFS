
#ifndef CONNECTFS_NODE_H
#define CONNECTFS_NODE_H

#include <string>
#include <set>
#include <memory>

class Node {
private:
    std::string node_id, name;
    bool is_file;
    std::set<std::shared_ptr<Node>> children;
public:
    explicit Node (const std::string& node_id);
    bool operator< (const std::shared_ptr<Node> &right);

    void addChild (const std::shared_ptr<Node> &child);
    bool isFile();
    std::set<std::shared_ptr<Node>>& getChildren ();
    std::string& getID ();
    std::string& getName();
};

#endif //CONNECTFS_NODE_H
