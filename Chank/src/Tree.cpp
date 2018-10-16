#include "Tree.h"
#include <sstream>

using chank::Tree;

Tree::Tree()
{
	const auto rootName = "root";
	this->root          = new Node(0, rootName, nullptr); // `root` has Id 0
	this->current       = this->root;
	this->length        = 1;
	this->lastId        = this->root->GetId();
}

Tree::~Tree()
{
	delete this->root;
}

void Tree::ChangeCurrent(const char* name)
{
	// TODO:
	this->current = this->root->Childs[0];
}

chank::Node* Tree::AddNode(const char* name)
{
	Node* newNode = new Node(this->length + 1, name, this->current);
	this->current->AddChild(newNode);
	this->lastId = this->length++;
	return newNode;
}

std::string Tree::GetCurrentPath() const
{
	std::vector<std::string> path;

	Node* current = this->current;
	while (current->Parent != nullptr)
	{
		path.emplace_back(this->current->Name);
		current = current->Parent;
	}
	path.emplace_back(this->root->Name);

	std::reverse(path.begin(), path.end());
	std::string result = "/";
	for (auto const& s : path)
		result += s + "/";

	result.pop_back(); // removes the last '/'
	return result;
}
