#pragma once
#include "DecisionProvider.h"
#include "UI.h"

class ConsoleDecisionProvider : public DecisionProvider
{
public:
    explicit ConsoleDecisionProvider(UI& ui)
        : m_ui(ui) {
    }

    void waitForRoll(Player& player) override
    {
        m_ui.waitForRoll(player);
    }

    bool decideBuyProperty(Player& p, PropertyTile& prop) override
    {
        return m_ui.requestBuyProperty(p, prop);
    }

    PropertyTile* decideMortgageProperty(Player& p) override
    {
        return m_ui.requestMortgageProperty(p);
    }

private:
    UI& m_ui;
};