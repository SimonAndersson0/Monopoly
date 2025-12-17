#pragma once
#include "UI.h"
#include "IGameUI.h"
class ConsoleUI : public IGameUI
{
public:
    void showMessage(const std::string& text) override;
    void showPlayerStatus(const Player& player) override;

    bool askYesNo(const std::string& question) override;
    int askNumber(const std::string& question, int min, int max) override;

    void showCard(const Card& card) override;
};

class ConsoleUI :
    public IGameUI
{
};


