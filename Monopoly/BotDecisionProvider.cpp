#include "BotDecisionProvider.h"
#include <cstdlib>   // for rand()
#include <ctime>     // for time()

BotDecisionProvider::BotDecisionProvider() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random
}

bool BotDecisionProvider::decideBuyProperty(Player& player, PropertyTile& property)
{
    if (player.getMoney() < property.getPrice())
        return false; // cannot afford

    return std::rand() % 2 == 0; // 50% chance to buy
}

int BotDecisionProvider::decideAuctionBid(Player& player, PropertyTile& property, int currentBid)
{
    int maxBid = player.getMoney();  // cannot bid more than what player has
    int bid = currentBid + std::rand() % 50; // bid increment randomly

    if (bid > maxBid) return 0; // pass
    return bid;
}
