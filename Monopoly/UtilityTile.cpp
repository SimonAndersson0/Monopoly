#include "UtilityTile.h"

//void UtilityTile::onLand(Player& player, GameManager& game)
//{
//    // Monopoly logic here
//    // buy property, pay rent, etc.
//}
int UtilityTile::getPrice() const
{
	return m_price;
}
int UtilityTile::getRent() const
{
	return m_rent; //rent on here is wierd since it needs to be calculated based on dice roll
}