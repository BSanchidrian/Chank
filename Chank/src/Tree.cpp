#include "Tree.h"
#include <sstream>
#include <algorithm>

// Default directory size in linux
#define DIR_SIZE 4096

using chank::Tree;

Tree::Tree()
{
    const auto rootName = "root";
    this->root = new Node(0, rootName, true, DIR_SIZE, nullptr); // `root` has Id 0
    this->current = this->root;
    this->length = 1;
    this->lastId = this->root->GetId();
}

Tree::~Tree()
{
    delete this->root;
}

void Tree::ChangeCurrent(const char* name)
{
    const auto sname = std::string(name);
	if (sname == std::string(".."))
	{
		auto parent = this->current->GetParent();
		this->current = (parent != nullptr) ? parent : this->current;
		return;
	}
    if(sname == std::string("/"))
    {
        this->current = this->root;
        return;
    }

    const auto node = this->current->FindChild(name);
	if (node == nullptr || !node->IsDir())
	{
		printf("-bash: cd: %s: Not a directory\n", name);
		return;
	}
    this->current = node;
}

chank::Node* Tree::CreateNode(const char* name, const bool isDir)
{
	if (const auto temp = this->GetCurrent()->FindChild(name); temp != nullptr)
	{
		printf("File/directory `%s': already exists\n", name);
		return nullptr;
	}

    const auto newNode = new Node(this->length + 1, name, isDir, isDir ? DIR_SIZE : 0, this->current);
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
