#include "TaxTile.h"
#include "GameManager.h"
#include "Player.h"
#include <string>

#include <iostream>

void TaxTile::onLand(Player& player, GameManager& game) {
	//tax the player the amount specified by m_taxAmount
	std::cout << "Taxed" + std::to_string(m_taxAmount) << "\n";
	game.takeMoney(player, m_taxAmount);

}