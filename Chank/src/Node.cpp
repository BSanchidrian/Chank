#include "Node.h"
#include <ctime>
#include <string>

using chank::Node;

Node::Node(const int id, const char* name, const bool isDir, const off_t size, Node* parent)
{
    this->id = id;
    strcpy(this->name, name);
    this->parent = parent;
    this->isDir = isDir;
    this->size = size;
    this->childs = std::vector<Node*>();
}

Node::~Node()
{
    this->childs.clear();
}

void Node::UpdateModificationDate()
{
    this->lastModification = time(nullptr);
}

Node* Node::AddChild(Node* node)
{
    node->UpdateModificationDate();
    this->childs.push_back(node);
    return node;
}