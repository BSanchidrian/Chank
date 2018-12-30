#include "Terminal.h"
#include "Commands.h"

#include <iostream>
#include <string>
#include <iterator>
#include <sstream>

using chank::Terminal;

Terminal::Terminal()
{
    this->tree = new Tree;
    this->commandDictionary = {
        {"pwd", &pwd },
        {"cd", &cd },
        {"ls", &ls },
        {"upload", &upload },
        {"mkdir", &mkdir },
        {"touch", &touch },
        {"lpwd", &lpwd },
        {"lls", &lls },
    };
}

Terminal::~Terminal()
{
    delete this->tree;
}

void Terminal::HandleInput() const
{
    std::string input;
    do
    {
        std::cout << "root@chank:~" << this->tree->GetCurrentPath() << "$ ";
        std::getline(std::cin, input);

        // Split std::string into std::vector
        // https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
        std::stringstream ss(input);
        const std::istream_iterator<std::string> begin(ss);
        const std::istream_iterator<std::string> end;
        std::vector<std::string> args(begin, end);

        const auto command = this->commandDictionary.find(args.front());
        if (command == this->commandDictionary.end())
        {
            printf("%s: command not found\n", input.c_str());
            continue;
        }
        args.erase(args.begin()); // removes the first argument (command name)
        // execute command
        command->second(this->tree, args);

    } while (input != "exit");
}