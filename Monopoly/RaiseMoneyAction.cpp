#include "RaiseMoneyAction.h"
#include "GameManager.h"
#include "Player.h"
#include "PayMoneyAction.h"
#include "BankruptcyAction.h"
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
    // If we can already pay, finish
    if (game.canAfford(m_player, m_requiredAmount))
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

    // If no way to raise money  bankruptcy
    if (!game.canRaiseMoney(m_player, m_requiredAmount))
    {
        game.queueAction(
            std::make_unique<BankruptcyAction>(
                m_player,
                m_creditor
            )
        );
        return;
    }

    // ONLY request decision — NOTHING ELSE
    game.requestDecision(
        MortgagePropertyDecision{
            &m_player,
            m_requiredAmount,
            m_creditor
        }
    );
}
