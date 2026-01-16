#include "BankruptcyAction.h"
#include "Player.h"
#include "GameManager.h"

BankruptcyAction::BankruptcyAction(Player& player, Player* creditor)
    : m_player(player)
    , m_creditor(creditor)
{
}

void BankruptcyAction::execute(GameManager& game)
{
    game.declareBankruptcy(m_player, m_creditor);
}