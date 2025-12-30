#include "PropertyTile.h"


void PropertyTile::onLand(Player& player, GameManager& game)
{
    if (!isOwned())
    {
        game.queueAction(
            std::make_unique<BuyPropertyAction>(player, *this)
        );
    }
    else if (owner() != &player)
    {
        game.queueAction(
            std::make_unique<PayRentAction>(player, *this)
        );
    }
}
