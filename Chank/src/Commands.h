#pragma once
#include "Tree.h"

namespace chank
{
    void pwd(Tree* tree, std::vector<std::string> args);
    void cd(Tree* tree, std::vector<std::string> args);
    void ls(Tree* tree, std::vector<std::string> args);
    void upload(Tree* tree, std::vector<std::string> args);
    void mkdir(Tree* tree, std::vector<std::string> args);
    void touch(Tree* tree, std::vector<std::string> args);

    void lpwd(Tree* tree, std::vector<std::string> args);
    void lls(Tree* tree, std::vector<std::string> args);
}
