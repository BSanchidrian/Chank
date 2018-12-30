#include "Tree.h"
#include <iostream>
#include "Terminal.h"

int main(int argc, char** argv)
{
    const auto terminal = new chank::Terminal();
    terminal->HandleInput();
    delete terminal;
    return 0;
}