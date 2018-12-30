#include "Node.h"
#include <ctime>

using chank::Node;

Node::Node(const int id, const char* name, bool isDir, off_t size, Node* parent)
{
	this->id = id;
	strcpy_s(this->name, strlen(name)+1, name);
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