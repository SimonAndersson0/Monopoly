#include "ConsoleDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"
#include <functional>

void ConsoleDecisionProvider::waitForRoll(
    Player& player,
    std::function<void()> onRolled)
{
    m_ui.waitForRoll(player);


    onRolled();
}

void ConsoleDecisionProvider::decideBuyProperty(
    Player& player,
    PropertyTile& property,
    std::function<void(bool)> onDecided)
{
    bool buy = m_ui.requestBuyProperty(player, property);
    onDecided(buy);
}

void ConsoleDecisionProvider::decideMortgageProperty(
    Player& player,
    int requiredAmount,
    std::function<void(int propertyId)> onDecided
) {
    int propertyId = m_ui.requestMortgageProperty(player);

	onDecided(propertyId);

}
