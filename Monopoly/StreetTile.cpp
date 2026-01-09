#include "StreetTile.h"
#include "GameManager.h"



//void StreetTile::onLand(Player& player, GameManager& game)
//{
//    // Monopoly logic here
//    // buy property, pay rent, etc.
//    std::cout << "Landed on Street: " << getName() << "  Price: " << std::to_string(getPrice()) << "  Color: " << getColorGroup() << "  Rent: " << getRent() << "\n";
//}
int StreetTile::calculateRent(const GameManager& game) const
{
	int rentIndex = 0;
	if (m_hasHotel) {
		rentIndex = 5; // Hotel rent
	}
	else {
		rentIndex = m_houses; // Rent based on number of houses
	}
	// Additional logic can be added here to check for color group ownership, etc.
	return m_rent[rentIndex];
}