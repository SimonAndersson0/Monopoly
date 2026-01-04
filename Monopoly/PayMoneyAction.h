#pragma once
#include "Action.h"
class Player;
class GameManager;

class PayMoneyAction : public Action
{
public:
    PayMoneyAction(
        Player& payer,
        int amount,
        Player* creditor = nullptr // nullptr = bank
    );

    void execute(GameManager& game) override;

private:
    Player& m_payer;
    int m_amount;
    Player* m_creditor;
};
