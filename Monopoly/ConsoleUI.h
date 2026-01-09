#pragma once
#include "UI.h"

class ConsoleUI : public UI
{
public:
    // Observer
    void onTurnStarted(const Player& player) override;
    void onDiceRolled(const Player& player, int total) override;
    void onPlayerMoved(const Player& player, const Tile& tile) override;
    void onMoneyChanged(const Player& player, int newAmount) override;
    void onGameOver() override;

    // Input
    void waitForRoll(const Player& player) override;
    bool requestBuyProperty(const Player&, const PropertyTile&) override;
    PropertyTile* requestMortgageProperty(const Player&) override;

    //temp
    void waitForEnter(const std::string& msg);
    int askInt(const std::string& prompt);
    std::string askString(const std::string& prompt);
    bool askYesNo(const std::string& prompt);
};
