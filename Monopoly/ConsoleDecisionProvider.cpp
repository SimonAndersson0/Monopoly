#include "ConsoleDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"
void ConsoleDecisionProvider::waitForRoll(Player& player)
{
    m_ui.waitForRoll(player);
}

bool ConsoleDecisionProvider::decideBuyProperty(
    Player& player,
    PropertyTile& property)
{
    return m_ui.requestBuyProperty(player, property);
}

PropertyTile* ConsoleDecisionProvider::decideMortgageProperty(
    Player& player)
{
    return m_ui.requestMortgageProperty(player);
}
