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
    if (game.canAfford(m_player,m_requiredAmount))
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

    
	if (!game.canRaiseMoney(m_player, m_requiredAmount))
    {
        // Cannot raise enough money, declare bankruptcy
        game.queueAction(
            std::make_unique<BankruptcyAction>(
                m_player,
                m_creditor
            )
        );
        return;
    }

    game.requestDecision(
        MortgagePropertyDecision{
            &m_player,
            m_requiredAmount,
            m_creditor
        });

}
