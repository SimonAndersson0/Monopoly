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

PropertyTile* ConsoleDecisionProvider::decideMortgageProperty(Player& player)
{
    const auto& props = player.getProperties();

    if (props.empty())
        return nullptr;

    m_ui.showMessage("Choose a property to mortgage:");

    for (size_t i = 0; i < props.size(); ++i)
    {
        m_ui.showMessage(
            std::to_string(i) + ": " + props[i]->getName()
        );
    }

    int choice = m_ui.askInt("Enter index (-1 to cancel):");

    if (choice < 0 || choice >= static_cast<int>(props.size()))
        return nullptr;

    return props[choice];
}