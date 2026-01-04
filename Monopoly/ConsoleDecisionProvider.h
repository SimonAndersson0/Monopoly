#pragma once
#include "DecisionProvider.h"
#include "UI.h"

class ConsoleDecisionProvider : public DecisionProvider
{
public:
    explicit ConsoleDecisionProvider(UI& ui) : m_ui(ui) {}

    bool decideBuyProperty(Player& player, PropertyTile& property) override;
    int decideAuctionBid(Player& player, PropertyTile& property, int currentBid) override;
	PropertyTile* decideMortgageProperty(Player& player) override;

    void waitForRoll(Player& player) override;

private:
    UI& m_ui;
};
