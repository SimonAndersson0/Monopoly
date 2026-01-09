#pragma once
#include "GameObserver.h"
#include <string>

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
    


    //temp
	virtual int requestPlayerCount() = 0;
	virtual std::string requestPlayerName(int index) = 0;
	virtual bool requestIsBot(const std::string& playerName) = 0;

};
