#include "BotDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"
#include <functional>


void BotDecisionProvider::waitForRoll(
    Player& player,
    std::function<void()> onRolled)
{
    onRolled(); // bot rolls immediately //remove the 0 not needed
}

void BotDecisionProvider::decideBuyProperty(
    Player& player,
    PropertyTile& property,
    std::function<void(bool)> onDecided)
{
    bool buy = true;
    onDecided(buy);
}

void BotDecisionProvider::decideMortgageProperty(Player& player) {

}

