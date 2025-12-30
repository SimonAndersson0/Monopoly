#pragma once
#include "Action.h"

class Player;
class PropertyTile;
class GameManager;

class PayRentAction :
    public Action
{
public:
    PayRentAction(Player& player, PropertyTile& property);

    void execute(GameManager& game) override;

private:
    Player& m_player;
    PropertyTile& m_property;
};

