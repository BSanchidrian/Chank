#pragma once
#include "Node.h"
// #include "Disk.h"
#include <vector>
#include <string>

namespace chank
{
class Tree
{
public:
    Tree();
    ~Tree();

    void ChangeCurrent(const char *name);
    Node *CreateNode(const char *name, const bool isDir);
    Node *CopyNode(const Node &node, const char *name);

    void Save();
    void Load();

    void DecrementLength() { this->length--; }
    std::string GetCurrentPath() const;
    Node *GetCurrent() const { return this->current; }

private:
    Node *root;    // Pointer to the `main` node
    Node *current; // Current node
    int length;    // Number of nodes
    int lastId;    // ID of the last node added
    // std::vector<Disk *> disks; // List of disks
};
} // namespace chank
