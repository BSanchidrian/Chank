#pragma once
#include "Tree.h"
#include <vector>

namespace chank
{
	void exit(Tree* tree, std::vector<std::string> &args);
    void pwd(Tree* tree, std::vector<std::string> &args);
    void cd(Tree* tree, std::vector<std::string> &args);
    void ls(Tree* tree, std::vector<std::string> &args);
	void mkdir(Tree* tree, std::vector<std::string> &args);
	void rmdir(Tree* tree, std::vector<std::string> &args);
	void rm(Tree* tree, std::vector<std::string> &args);
	void touch(Tree* tree, std::vector<std::string> &args);
	void mv(Tree* tree, std::vector<std::string> &args);
	void cp(Tree* tree, std::vector<std::string> &args);

    void lpwd(Tree* tree, std::vector<std::string> &args);
	void lcd(Tree* tree, std::vector<std::string> &args);
	void lls(Tree* tree, std::vector<std::string> &args);
	void upload(Tree* tree, std::vector<std::string> &args);
}
