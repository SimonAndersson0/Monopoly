#pragma once
#include "GameObserver.h"

class Player;
class PropertyTile;

class UI : public GameObserver
{
public:
    virtual ~UI() = default;

    // ---- Input requests (typed, contextual) ----
    virtual void waitForRoll(const Player& player) = 0;

    virtual bool requestBuyProperty(
        const Player& player,
        const PropertyTile& property
    ) = 0;

    virtual PropertyTile* requestMortgageProperty(
        const Player& player
    ) = 0;
};
