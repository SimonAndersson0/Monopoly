#pragma once
#include "DecisionProvider.h"
#include "UI.h"
#include <functional>
class Player;
class PropertyTile;

class ConsoleDecisionProvider : public DecisionProvider
{
public:
    explicit ConsoleDecisionProvider(UI& ui)
        : m_ui(ui) {
    }

    virtual void waitForRoll(
        Player& player,
        std::function<void()> onRolled
    ) override;

    // Buy property  yes/no
    virtual void decideBuyProperty(
        Player& player,
        PropertyTile& property,
        std::function<void(bool)> onDecided
    ) override;

    void decideMortgageProperty(Player& player) override;


private:
    UI& m_ui;
};