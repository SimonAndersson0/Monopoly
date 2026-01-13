#pragma once

class Player;
class PropertyTile;

class DecisionProvider
{
public:
    virtual ~DecisionProvider() = default;

    virtual void waitForRoll(Player& player) = 0;
    virtual bool decideBuyProperty(Player& player, PropertyTile& property) = 0;
    virtual PropertyTile* decideMortgageProperty(Player& player) = 0;
};
