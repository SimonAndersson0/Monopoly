#include "ConsoleUI.h"
#include <iostream>
#include <limits>
#include <cctype>

void ConsoleUI::showMessage(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void ConsoleUI::waitForEnter(const std::string& msg)
{
    std::cout << msg;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ConsoleUI::askInt(const std::string& prompt)
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

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

std::string ConsoleUI::askString(const std::string& prompt)
{
    std::string value;
    std::cout << prompt << " ";
    std::getline(std::cin, value);
    return value;
}

bool ConsoleUI::askYesNo(const std::string& prompt)
{
    char input;
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        input = std::tolower(input);
        if (input == 'y') return true;
        if (input == 'n') return false;

        std::cout << "Invalid input. Please enter y or n.\n";
    }
}
