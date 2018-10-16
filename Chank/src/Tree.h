#pragma once
#include "Node.h"

namespace chank
{
	class Tree
	{
	private:
		Node* root;    // Pointer to the `main` node
		Node* current; // Current node
		int length;    // Number of nodes
		int lastId;    // ID of the last node added
	public:
		Tree();
		~Tree();

		void ChangeCurrent(const char* name);

		/**
		 * Adds a new new node (file/directory) as child of the current node
		 * returns: the new node
		 */
		Node* AddNode(const char* name);

		std::string GetCurrentPath() const;
	};
}
