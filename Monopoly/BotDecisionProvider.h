#pragma once
#include "DecisionProvider.h"
#include <functional>
class Player;
class PropertyTile;

class BotDecisionProvider : public DecisionProvider
{
public:
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

    void decideMortgageProperty(
        Player& player,
        int requiredAmount,
        std::function<void(int propertyId)> onDecided
    ) override;
};
