#pragma once
class Player;
class PropertyTile;

struct Decision
{
    enum class Type
    {
        RollDice,
        BuyProperty,
        MortgageProperty,
        // later:
        // AuctionBid,
        // Trade,
        // Mortgage
    };

    Type type;
    Player* player = nullptr;

    // payloads (only one used depending on type)
    PropertyTile* property = nullptr;
    int intValue = 0;     // e.g. dice roll, auction bid
    Player* Creditor;
    bool boolValue = false;
};

