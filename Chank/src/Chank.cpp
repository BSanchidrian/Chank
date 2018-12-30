#include "Terminal.h"
#include <iostream>

int main(int argc, char** argv)
{
    const auto terminal = new chank::Terminal();
    terminal->HandleInput();
    delete terminal;
    return 0;
}