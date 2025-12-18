#include "TaxTile.h"
#include "GameManager.h"
#include "Player.h"

#include <iostream>

void TaxTile::onLand(Player& player, GameManager& game) {
	//tax the player the amount specified by m_taxAmount
	std::cout << "Taxed";
	game.takeMoney(player, m_taxAmount);

}