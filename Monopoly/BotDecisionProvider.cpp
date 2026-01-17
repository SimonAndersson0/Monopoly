#include "BotDecisionProvider.h"
#include "Player.h"
#include "PropertyTile.h"
#include <functional>
#include <iostream>


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
void BotDecisionProvider::decideMortgageProperty(
    Player& player,
    int requiredAmount,
    std::function<void(int propertyId)> onDecided
){
   int propertyId;
   player.getNoneMortgagedProperties().empty() ? propertyId = -1 : propertyId = player.getNoneMortgagedProperties().front()->getID(); //mortgage first property if any avilable
   
   std::cout << "Bot decided to mortgage property ID: " << propertyId << "\n";
   //propertyId = -1;
   onDecided(propertyId);
}
