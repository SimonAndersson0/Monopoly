#include "PayRentAction.h"

#include "Player.h"
#include "PropertyTile.h"
#include "GameManager.h"
#include "DecisionProvider.h"
#include "RaiseMoneyAction.h"
#include "BankruptcyAction.h"

PayRentAction::PayRentAction(Player& player, PropertyTile& property)
    : m_player(player)
    , m_property(property)
{
}

void PayRentAction::execute(GameManager& game)
{
    Player* owner = m_property.getOwner();
    int rent = m_property.getRent();

    if (game.canAfford(m_player, rent))
    {
        game.transferMoney(m_player, *owner, rent);
        return;
    }

    if (game.canRaiseMoney(m_player, rent))
    {
        game.queueAction(
            std::make_unique<RaiseMoneyAction>(
                m_player, rent, owner
            )
        );
    }
    else
    {
        game.queueAction(
            std::make_unique<BankruptcyAction>(
                m_player, owner
            )
        );
    }
}