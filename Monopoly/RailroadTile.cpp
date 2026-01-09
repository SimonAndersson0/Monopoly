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
    return 25 * (1 << (owned - 1)); // 25, 50, 100, 200
}
