#include "UtilityTile.h"
#include "GameManager.h"

//void UtilityTile::onLand(Player& player, GameManager& game)
//{
//    // Monopoly logic here
//    // buy property, pay rent, etc.
//}

int UtilityTile::calculateRent(const GameManager& game) const
{
    int diceTotal = game.getSumOfLastRoll();
    int owned = game.countOwnedUtilities(*getOwner());

    return diceTotal * (owned == 1 ? 4 : 10);
}
