#include "Tree.h"
#include <sstream>

// Default directory size in linux
#define DIR_SIZE 4096

using chank::Tree;

Tree::Tree()
{
	const auto rootName = "root";
	this->root          = new Node(0, rootName, true, DIR_SIZE, nullptr); // `root` has Id 0
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
	this->current = this->root->GetChilds()[0];
}

chank::Node* Tree::CreateNode(const char* name, const bool isDir)
{
	Node* newNode = new Node(this->length + 1, name, isDir, isDir ? DIR_SIZE : 0, this->current);
	this->current->AddChild(newNode);
	this->lastId = this->length++;
	return newNode;
}

std::string Tree::GetCurrentPath() const
{
	std::vector<std::string> path;

	Node* current = this->current;
	while (current->GetParent() != nullptr)
	{
		path.emplace_back(this->current->GetName());
		current = current->GetParent();
	}
	path.emplace_back(this->root->GetName());

	std::reverse(path.begin(), path.end());
	std::string result = "/";
	for (auto const& s : path)
		result += s + "/";

	result.pop_back(); // removes the last '/'
	return result;
}
