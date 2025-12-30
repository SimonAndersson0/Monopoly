#include "ConsoleDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"

bool ConsoleDecisionProvider::decideBuyProperty(Player& player, PropertyTile& property)
{
    return m_ui.askYesNo(
        "Do you want to buy " + property.getName() +
        " for " + std::to_string(property.getPrice()) + "?"
    );
}

int ConsoleDecisionProvider::decideAuctionBid(Player& player, PropertyTile& property, int currentBid)
{
    return m_ui.askInt("Enter bid (current: " + std::to_string(currentBid) + "):");
}
