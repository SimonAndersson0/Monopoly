#include "BotDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"

bool BotDecisionProvider::decideBuyProperty(
    Player& player,
    PropertyTile& property)
{
    return player.getMoney() > property.getPrice();
}

PropertyTile* BotDecisionProvider::decideMortgageProperty(
    Player&)
{
    return nullptr;
}
