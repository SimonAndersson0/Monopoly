#include "BuyPropertyAction.h"

#include "Player.h"
#include "PropertyTile.h"
#include "GameManager.h"
#include "DecisionProvider.h" // Add this include to resolve incomplete type errors
// #include "AuctionAction.h"

BuyPropertyAction::BuyPropertyAction(Player& player, PropertyTile& property)
    : m_player(player)
    , m_property(property)
{
}

void BuyPropertyAction::execute(GameManager& game)
{
    bool buy = m_player.controller()
        .decideBuyProperty(m_player, m_property); //always needs decision provider maybe all of them unsure

    if (buy && game.canAfford(m_player, m_property.getPrice()))
    {
        game.buyProperty(m_player, m_property);
    }
    else
    {
        // Queue auction later if you want
        // game.queueAction(std::make_unique<AuctionAction>(m_property));
    }
}
