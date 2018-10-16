#pragma once
#include <vector>

namespace chank
{
	class Node
	{
	private:
		int id; // Node unique identifier
	public:
		Node(const int id, const char* name, Node* parent);
		~Node();

		/**
		 * Adds a new node as child of this one
		 * returns: the new node
		 */
		Node* AddChild(Node* node);

		// GETTERS
		int GetId() const;

	public:                        // public variables
		Node* Parent;              // Node Parent
		char Name[25]{};           // TODO: preguntar por que tiene que ser char de longitud fija
		std::vector<Node*> Childs; // Nodes that belong to the current one (directory)
	};
}
