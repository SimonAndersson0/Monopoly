#pragma once

class Player;
class PropertyTile;

class DecisionProvider
{
public:
    virtual ~DecisionProvider() = default;

    virtual bool decideBuyProperty(Player& player,
        PropertyTile& property) = 0;

    virtual int decideAuctionBid(Player& player,
        PropertyTile& property,
        int currentBid) = 0;
};
