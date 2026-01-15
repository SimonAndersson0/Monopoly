#pragma once
#include <functional>

class Player;
class PropertyTile;

class DecisionProvider
{
public:
    virtual ~DecisionProvider() = default;

    // Roll dice  no value needed, just "ready"
    virtual void waitForRoll(
        Player& player,
        std::function<void()> onRolled
    ) = 0;

    // Buy property  yes/no
    virtual void decideBuyProperty(
        Player& player,
        PropertyTile& property,
        std::function<void(bool)> onDecided
    ) = 0;

    virtual void decideMortgageProperty(
        Player& player,
		int requiredAmount,
		std::function<void(int propertyId)> onDecided
    ) = 0;

    // You will add more later:
    // mortgage
    // trade
    // auction bid
};

