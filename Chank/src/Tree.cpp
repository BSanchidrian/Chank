#include "Tree.h"
#include "BinaryUtils.h"

#include <algorithm>
#include <ctime>

// Default directory size in linux
#define DIR_SIZE 4096

using chank::Tree;

#include "Node.h"
using chank::Node;

Tree::Tree()
{
	this->Load();

	if (this->root == nullptr) // if couldn't be loaded correctly
	{
		const auto rootName = "root";
		this->root = new Node(0, rootName, true, DIR_SIZE, time(nullptr), nullptr); // `root` has Id 0
		this->length = 1;
		this->lastId = 0;
	}
	this->current = this->root;
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

    const auto newNode = new Node(++this->lastId, name, isDir, isDir ? DIR_SIZE : 0, time(nullptr), this->current);
    this->current->AddChild(newNode);
	this->length++;
	this->Save();
    return newNode;
}

void Tree::Save()
{
	chank::BinaryOut file("tree.dat");
	// Tree information
	file << this->length;
	file << this->lastId;

	// Nodes information
	this->root->Save(file);
	file.close();
}

Node* test(chank::BinaryIn& file)
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
		auto child = test(file);
		child->SetParent(node);
		node->AddChild(child);
	}

	return node;
}

void Tree::Load()
{
	chank::BinaryIn file("tree.dat");
	if (!file.good()) return;

	// Tree information
	file >> this->length;
	file >> this->lastId;

	this->root = test(file);
	file.close();
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
