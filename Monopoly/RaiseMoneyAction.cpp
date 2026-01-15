#include "RaiseMoneyAction.h"
#include "GameManager.h"
#include "Player.h"
#include "PayMoneyAction.h"
#include "BankruptcyAction.h"
#include "DecisionProvider.h"
#include "Decision.h"

#include <memory>

RaiseMoneyAction::RaiseMoneyAction(
    Player& player,
    int requiredAmount,
    Player* creditor
) :
    m_player(player),
    m_requiredAmount(requiredAmount),
    m_creditor(creditor)
{
}
void RaiseMoneyAction::execute(GameManager& game)
{
    // If we already have enough cash, continue
    if (m_player.getMoney() >= m_requiredAmount)
    {
        game.queueAction(
            std::make_unique<PayMoneyAction>(
                m_player,
                m_requiredAmount,
                m_creditor
            )
        );
        return;
    }

    // Ask the GameManager to request a decision
    game.requestDecision({
        Decision::Type::MortgageProperty,
        &m_player,
        nullptr,              // no property yet
        m_requiredAmount,     // optional context
        m_creditor            // optional context
        });


    //MOVE LOGIC TO SUBMIT
    PropertyTile* property =
        m_player.controller().decideMortgageProperty(m_player);

    if (!property)
    {
        game.queueAction(
            std::make_unique<BankruptcyAction>(
                m_player, m_creditor
            )
        );
        return;
    }

    // GameManager enforces rules
    if (!game.canMortgage(m_player, *property))
    {
        // Try again
        game.queueAction(
            std::make_unique<RaiseMoneyAction>(
                m_player, m_requiredAmount, m_creditor //create new action
            )
        );
        return;
    }

    game.mortgageProperty(m_player, *property);

    // Try again after raising money
    game.queueAction(
        std::make_unique<RaiseMoneyAction>(
            m_player, m_requiredAmount, m_creditor
        )
    );
}
