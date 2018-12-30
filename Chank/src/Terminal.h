#pragma once
#include "Tree.h"
#include <string>
#include <map>
#include <functional>

namespace chank
{
    class Terminal
    {
    private:
        Tree* tree; // file system
        // Commands dictionary {
        //  key = string (command name)
        //  value = function to execute void(Tree, vector<arguments>)
        std::map<std::string, std::function<void(Tree*, std::vector<std::string>)>> commandDictionary;
    public:
        Terminal();
        ~Terminal();
        void HandleInput() const;
    };
}
