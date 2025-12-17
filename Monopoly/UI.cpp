#include "UI.h"
#include <iostream>
#include <limits>

void UI::showMessage(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void UI::waitForEnter()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int UI::askInt(const std::string& prompt)
{
    int value;

    while (true)
    {
        std::cout << prompt << " ";
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        // Invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

std::string UI::askString(const std::string& prompt)
{
    std::string value;
    std::cout << prompt << " ";
    std::getline(std::cin, value);
    return value;
}
