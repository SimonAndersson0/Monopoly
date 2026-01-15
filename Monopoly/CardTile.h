#pragma once

#include <string>
#include "ActionTile.h"
#include "CardTileType.h"

class Player;
class GameManager;

class CardTile :
    public ActionTile
{
public:
    explicit CardTile(const int& ID,const std::string& name,const CardTileType type); //not exactly sure what explicit does

    CardTileType getType() const;
    void onLand(Player& player, GameManager& game) override;

private:
    CardTileType m_type;
};

