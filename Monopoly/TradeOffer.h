#pragma once
#include <vector>
class Player;
class PropertyTile;


struct TradeOffer
{
    Player* proposer;
    Player* target;

    std::vector<PropertyTile*> giveProperties;
    std::vector<PropertyTile*> receiveProperties;

    int giveMoney = 0;
    int receiveMoney = 0;

    bool proposerAccepted = true; // proposer accepts by default
    bool targetAccepted = false;
};
