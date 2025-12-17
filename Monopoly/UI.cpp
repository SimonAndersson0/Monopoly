#include "UI.h"
#include <iostream>
#include <limits>

void UI::showMessage(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void UI::waitForEnter(const std::string& msg)
{
    std::cout << msg;
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

char UI::askYesNo(const std::string& prompt)
{
    char input;
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        input = std::tolower(input); // normalize input
        if (input == 'y' || input == 'n')
            return input;

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}