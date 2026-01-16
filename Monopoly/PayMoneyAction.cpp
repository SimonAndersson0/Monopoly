#include "PayMoneyAction.h"
#include "GameManager.h"
#include "RaiseMoneyAction.h"
#include "BankruptcyAction.h"

PayMoneyAction::PayMoneyAction(
    Player& payer,
    int amount,
    Player* creditor
) :
    m_payer(payer),
    m_amount(amount),
    m_creditor(creditor)
{
}

void PayMoneyAction::execute(GameManager& game)
{
    // Can pay immediately
    if (game.canAfford(m_payer, m_amount))
    {
        if (m_creditor)
            game.transferMoney(m_payer, *m_creditor, m_amount);
        else
            game.takeMoney(m_payer, m_amount); // pay bank

        return;
    }

    // Can raise money mortgage/sell/etc
    if (game.canRaiseMoney(m_payer, m_amount))
    {
        game.queueAction(
            std::make_unique<RaiseMoneyAction>(
                m_payer, m_amount, m_creditor
            )
        );
    }
    else
    {
        game.queueAction(
            std::make_unique<BankruptcyAction>(
                m_payer, m_creditor
            )
        );
    }

}
