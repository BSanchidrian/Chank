#include "Node.h"

using chank::Node;

Node::Node(const int id, const char* name, Node* parent)
{
	this->id = id;
	strcpy_s(this->Name, strlen(name)+1, name);
	this->Parent = parent;
	this->Childs = std::vector<Node*>();
}

Node::~Node()
{
	this->Childs.clear();
}

Node* Node::AddChild(Node* node)
{
	this->Childs.push_back(node);
	return node;
}

int Node::GetId() const
{
	return this->id;
}