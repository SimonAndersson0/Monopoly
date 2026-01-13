#pragma once
class Player;
class PropertyTile;

struct Decision
{
    enum class Type
    {
        BuyProperty,
        MortgageProperty,
        Trade,
        RollDice
    };

    Type type;
    Player* player = nullptr;

    // payload
    PropertyTile* property = nullptr;
};

