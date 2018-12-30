#pragma once
#include <vector>

namespace chank
{
    class Node
    {
    public:
        Node(const int id, const char* name, bool isDir, off_t size, Node* parent);
        ~Node();

        /**
         * Adds a new node as child of this one
         * returns: the new node
         */
        Node* AddChild(Node* node);

        /**
         * Sets the current datetime as the lastest modification date of the node
         */
        void UpdateModificationDate();

        // GETTERS
        int GetId() const { return this->id; };
        char* GetName() { return this->name; }
        Node* GetParent() const { return this->parent; };
        std::vector<Node*> GetChilds() const { return this->childs; }
        bool IsDir() const { return this->isDir; }
        off_t GetSize() const { return this->size; }
        time_t GetLastModification() const { return this->lastModification; }

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
