#pragma once
#include <string>

class UI
{
public:
    virtual ~UI() = default;

    // Output
    virtual void showMessage(const std::string& msg) = 0;

    // Input
    virtual void waitForEnter(const std::string& msg) = 0;
    virtual int askInt(const std::string& prompt) = 0;
    virtual std::string askString(const std::string& prompt) = 0;
    virtual bool askYesNo(const std::string& prompt) = 0;
};
