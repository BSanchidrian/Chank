#include "Tree.h"
#include "BinaryUtils.h"

#include <algorithm>
#include <ctime>

#define DIR_SIZE 4096 // Default directory size in linux
#define DISK_NUM 4
#define DISK_SIZE 33554432 // 32 mb

using chank::Tree;

#include "Node.h"
using chank::Node;

Tree::Tree() : root(nullptr)
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

	// for (auto i = 0; i < DISK_NUM; i++)
	// {
	//     auto disk = new Disk(i, DISK_SIZE);
	//     this->disks.push_back(disk);
	// }
}

Tree::~Tree()
{
	delete this->root;
	delete this->current;
	// for (auto &disk : this->disks)
	// 	delete disk;
}

void Tree::ChangeCurrent(const char *name)
{
	const auto sname = std::string(name);
	if (sname == std::string(".."))
	{
		auto parent = this->current->GetParent();
		this->current = (parent != nullptr) ? parent : this->current;
		return;
	}
	if (sname == std::string("/"))
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

chank::Node *Tree::CreateNode(const char *name, const bool isDir)
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

chank::Node *Tree::CopyNode(const Node &node, const char *name)
{
	const auto newNode = new Node(++this->lastId, name, node.IsDir(), node.GetSize(), time(nullptr), this->current);
	this->current->AddChild(newNode);
	this->length++;

	for (const auto &child : node.GetChilds())
	{
		newNode->AddChild(new Node(++this->lastId, child->GetName(), child->IsDir(), child->GetSize(), time(nullptr), newNode));
		this->length++;
	}

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

void Tree::Load()
{
	chank::BinaryIn file("tree.dat");
	if (!file.good())
		return;

	// Tree information
	file >> this->length;
	file >> this->lastId;

	this->root = Node::Load(file);
	file.close();
}

std::string Tree::GetCurrentPath() const
{
	std::vector<std::string> path;

	Node *current = this->current;
	while (current->GetParent() != nullptr)
	{
		path.emplace_back(this->current->GetName());
		current = current->GetParent();
	}
	path.emplace_back(this->root->GetName());

	std::reverse(path.begin(), path.end());
	std::string result = "/";
	for (auto const &s : path)
		result += s + "/";

	result.pop_back(); // removes the last '/'
	return result;
}
