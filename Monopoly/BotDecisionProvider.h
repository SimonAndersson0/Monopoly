#pragma once
#include "DecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"

class BotDecisionProvider : public DecisionProvider
{
public:
    BotDecisionProvider();
    bool decideBuyProperty(Player& player, PropertyTile& property) override;
    int decideAuctionBid(Player& player, PropertyTile& property, int currentBid) override;
    PropertyTile* decideMortgageProperty(Player& player) override;
    void waitForRoll(Player& player) override;
};
