#include "ConsoleDecisionProvider.h"

void ConsoleDecisionProvider::waitForRoll(Player& player)
{
    m_ui.waitForRoll(player);
}

bool ConsoleDecisionProvider::decideBuyProperty(
    Player& player,
    PropertyTile& property)
{
    return m_ui.askBuyProperty(player, property);
}

PropertyTile* ConsoleDecisionProvider::decideMortgageProperty(
    Player& player)
{
    return m_ui.askMortgageProperty(player);
}
