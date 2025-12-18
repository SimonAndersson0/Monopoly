#include "StreetTile.h"
#include <iostream>


void StreetTile::onLand(Player& player, GameManager& game)
{
    // Monopoly logic here
    // buy property, pay rent, etc.
    std::cout << "Landed on Street: " << getName() << "  Price: " << std::to_string(getPrice()) << "  Color: " << getColorGroup() << "  Rent: " << getRent() << "\n";
}
