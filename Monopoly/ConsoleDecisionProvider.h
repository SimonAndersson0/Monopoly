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

    void waitForRoll(
        Player& player,
        std::function<void()> onRolled
    ) override;

    // Buy property  yes/no
    void decideBuyProperty(
        Player& player,
        PropertyTile& property,
        std::function<void(bool)> onDecided
    ) override;

    void decideMortgageProperty(
        Player& player,
        int requiredAmount,
        std::function<void(int propertyId)> onDecided
    ) override;


private:
    UI& m_ui;
};