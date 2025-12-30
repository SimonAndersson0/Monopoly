#pragma once

#include "Action.h"

class Player;
class PropertyTile;
class GameManager;
class UI;

class BuyPropertyAction : public Action
{
public:
    BuyPropertyAction(Player& player, PropertyTile& property);

    void execute(GameManager& game) override;

private:
    Player& m_player;
    PropertyTile& m_property;
};
