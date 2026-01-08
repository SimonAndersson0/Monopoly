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
};
