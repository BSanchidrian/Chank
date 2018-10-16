#include "Terminal.h"
#include <iostream>
#include <string>

using chank::Terminal;

Terminal::Terminal()
{
	this->tree = new Tree;
	// temp
	this->tree->AddNode("test");
	//this->tree->ChangeCurrent("test");
	this->tree->AddNode("yolo");
	this->tree->ChangeCurrent("test");
}

Terminal::~Terminal()
{
	delete this->tree;
}

void Terminal::HandleInput()
{
	std::string input;
	do
	{
		std::cout << "root@chank:~" << this->tree->GetCurrentPath() << "$ ";
		std::cin >> input;

		printf("%s: command not found\n", input.c_str());

	} while (input != "exit");
}
