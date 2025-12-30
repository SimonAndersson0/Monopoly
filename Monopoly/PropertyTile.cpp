#include "PropertyTile.h"
#include "Player.h"
#include "GameManager.h"
#include "BuyPropertyAction.h"
#include "PayRentAction.h"


void PropertyTile::onLand(Player& player, GameManager& game)
{
    if (getOwner()==nullptr)
    {
        game.queueAction(
            std::make_unique<BuyPropertyAction>(player, *this)
        );
    }
    else if (getOwner() != &player)
    {
        game.queueAction(
            std::make_unique<PayRentAction>(player, *this)
        );
    }
}

void PropertyTile::setOwner(Player& player)
{
    m_owner = &player;
}
