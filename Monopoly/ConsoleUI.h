#pragma once
#include "UI.h"

class ConsoleUI : public UI
{
public:
    void showMessage(const std::string& msg) override;
    void waitForEnter(const std::string& msg) override;
    int askInt(const std::string& prompt) override;
    std::string askString(const std::string& prompt) override;
    bool askYesNo(const std::string& prompt) override;
};
