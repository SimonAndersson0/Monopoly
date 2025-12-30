#pragma once
#include "Action.h"

class Player;

class BankruptcyAction :
    public Action
{
public:
    BankruptcyAction(Player& player, Player& creditor);

    void execute(GameManager& game) override;

private:
    Player& m_player;
    Player& m_creditor;
};

