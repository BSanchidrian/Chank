#include "Node.h"
#include <ctime>
#include <cstring>
#include <string>
#include <vector>

using chank::Node;
using chank::BinaryOut;
using chank::BinaryIn;

Node::Node(const int id, const char* name, const bool isDir, const off_t size, const time_t lastModification, Node* parent)
{
    this->id = id;
    strcpy(this->name, name);
    this->parent = parent;
    this->isDir = isDir;
    this->size = size;
	this->lastModification = lastModification;
    this->childs = std::vector<Node*>();
}

Node::~Node()
{
	for (auto& child : this->childs)
		delete child;
    this->childs.clear();
}

void Node::UpdateModificationDate()
{
    this->lastModification = time(nullptr);
}

Node* Node::AddChild(Node* node)
{
    this->childs.push_back(node);
    return this;
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

Node* Node::UpdateNode(const char *name)
{
	strcpy(this->name, name);
	return this;
}

void Node::RemoveChild(const int id)
{
	int index = 0;
	for (auto& node : this->childs)
	{
		if (node->GetId() == id)
		{
			this->childs.erase(this->childs.begin() + index);
			delete node;
			break;
		}
		index++;
	}
}

void Node::Save(BinaryOut& file) const
{
	file << this->id;
	file << this->name;
	file << this->lastModification;
	file << this->size;
	file << this->isDir;
	file << this->childs.size();

	for (const auto &child : this->childs)
	{
		child->Save(file);
	}
}

Node* Node::Load(BinaryIn& file)
{
	int id;
	Node* parent;
	char name[NAME_MAX_LENGTH]{};
	bool isDir;
	int childNum;
	off_t size;
	time_t lastModification;

	file >> id;
	file >> name;
	file >> lastModification;
	file >> size;
	file >> isDir;
	file >> childNum;

	auto node = new Node(id, name, isDir, size, lastModification, nullptr);
	for (; childNum > 0; childNum--)
	{
		auto child = Node::Load(file);
		child->SetParent(node);
		node->AddChild(child);
	}

	return node;
}
