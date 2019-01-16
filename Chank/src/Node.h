#pragma once
#include <vector>
#include <ctime>
#include <sys/stat.h>

namespace chank
{
    class Node
    {
    public:
        Node(const int id, const char* name, const bool isDir, const off_t size, Node* parent);
        ~Node();

        /**
         * Adds a new node as child of this one
         * returns: the new node
         */
        Node* AddChild(Node* node);

		Node* FindChild(const char *name) const;
		Node* FindChild(const int id) const;
		Node* UpdateNode(const char *name);
		void RemoveChild(const int id);

        /**
         * Sets the current datetime as the lastest modification date of the node
         */
        void UpdateModificationDate();

        // GETTERS
        int GetId() const { return this->id; };
        const char* GetName() const { return this->name; }
        Node* GetParent() const { return this->parent; };
        std::vector<Node*> GetChilds() const { return this->childs; }
        bool IsDir() const { return this->isDir; }
        off_t GetSize() const { return this->size; }
        time_t GetLastModification() const { return this->lastModification; }

		bool operator==(const Node& a) { return this->id == a.GetId(); }

    private:
        int id;	                    // Node unique identifier
        Node* parent;               // Node parent
        char name[25]{};            // Node name
        bool isDir;                 // Is directory flag
        std::vector<Node*> childs;  // Nodes that belong to the current one (directory)
        off_t size;                 // Node size
        time_t lastModification;    // Last modification date
    };
}
