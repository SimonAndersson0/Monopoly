#include "UI.h"
#include <iostream>

void UI::showMessage(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void UI::waitForEnter()
{
    std::cout << "Press ENTER to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
