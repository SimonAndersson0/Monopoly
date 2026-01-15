#include "CardTile.h"

CardTile::CardTile(const int& ID,const std::string& name, const CardTileType type)
	: ActionTile(ID,name), m_type(type)
{
}

CardTileType CardTile::getType() const
{
    return m_type;
}

void CardTile::onLand(Player& player, GameManager& game){
	//draw card from appropriate deck and apply its effect
}