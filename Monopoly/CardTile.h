#pragma once

#include <string>
#include "ActionTile.h"
#include "CardTileType.h"

class CardTile :
    public ActionTile
{
public:
    CardTile(std::string name, CardTileType type);

    void onLand(Player& player, GameManager& game) override;

private:
    CardTileType m_type;
};

