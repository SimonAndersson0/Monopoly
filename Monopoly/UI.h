#pragma once
#include <string>

class UI
{
public:
    // Output
    void showMessage(const std::string& msg);

    // Input helpers
    void waitForEnter(const std::string& msg);

    int askInt(const std::string& prompt);

    std::string askString(const std::string& prompt);

    char askYesNo(const std::string& prompt);


};
