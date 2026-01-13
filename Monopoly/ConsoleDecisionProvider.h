#pragma once
#include "DecisionProvider.h"
#include "UI.h"

class ConsoleDecisionProvider : public DecisionProvider
{
public:
    explicit ConsoleDecisionProvider(UI& ui)
        : m_ui(ui) {
    }

    void waitForRoll(Player& player) override;


    bool decideBuyProperty(Player& player, PropertyTile& property) override;


    PropertyTile* decideMortgageProperty(Player& player) override;


private:
    UI& m_ui;
};