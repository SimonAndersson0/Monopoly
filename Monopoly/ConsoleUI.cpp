#include "ConsoleUI.h"
#include <iostream>

void ConsoleUI::showMessage(const std::string& text)
{
    std::cout << text << "\n";
}

bool ConsoleUI::askYesNo(const std::string& question)
{
    std::cout << question << " (y/n): ";
    char c;
    std::cin >> c;
    return c == 'y' || c == 'Y';
}
