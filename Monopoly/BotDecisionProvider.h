#pragma once
#include "DecisionProvider.h"

class BotDecisionProvider : public DecisionProvider
{
public:
    void waitForRoll(Player&) override {}

    bool decideBuyProperty(
        Player& player,
        PropertyTile& property
    ) override;

    PropertyTile* decideMortgageProperty(
        Player& player
    ) override;
};
