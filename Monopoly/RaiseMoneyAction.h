#pragma once
#include "Action.h"
class Player;
class GameManager;


class RaiseMoneyAction :
    public Action
{
public:
    RaiseMoneyAction(Player& player, int requiredAmount, Player* creditor);

    void execute(GameManager& game) override;

private:
    Player& m_player;
    int m_requiredAmount;
    Player* m_creditor;
};

