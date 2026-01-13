#include "RailroadTile.h"
#include <string>
#include <vector>
#include "GameManager.h"
//int RailroadTile::getPrice() const
//{
//	return m_price;
//}
//std::vector<int> RailroadTile::getRent() const
//{
//	return m_rent;
//}


int RailroadTile::calculateRent(const GameManager& game) const
{
    int owned = game.countOwnedRailroads(*getOwner());
    int rent = m_rent[owned];
    return rent;
}
