#include "Node.h"
#include <ctime>
#include <string>
#include <algorithm>

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

Node* Node::FindChild(const char *name) const
{
	if(this->childs.empty())
		return nullptr;

	for (auto* node : this->childs)
		if (std::string(node->GetName()) == std::string(name))
			return node;

	return nullptr;
}

Node* Node::FindChild(const int id) const
{
	if (this->childs.empty())
		return nullptr;

	for (auto* node : this->childs)
		if (node->GetId() == id)
			return node;

	return nullptr;
}

Node* Node::UpdateNode()
{
	return nullptr;
}

void Node::RemoveNode()
{
	// To remove a directory it has to be empty (no childs)
	if (this->isDir && !this->childs.empty())
		return;

	//this->pare

}