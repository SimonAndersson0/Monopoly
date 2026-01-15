#include "BuyPropertyAction.h"

#include "Player.h"
#include "PropertyTile.h"
#include "GameManager.h"
#include "DecisionProvider.h" // Add this include to resolve incomplete type errors
// #include "AuctionAction.h"
#include "Decision.h"

BuyPropertyAction::BuyPropertyAction(Player& player, PropertyTile& property)
    : m_player(player)
    , m_property(property)
{
}

void BuyPropertyAction::execute(GameManager& game)
{
    // Do NOT ask the controller here
    // Do NOT buy property here

    game.requestDecision(Decision{
        Decision::Type::BuyProperty,
        &m_player,
        &m_property
        });
}

