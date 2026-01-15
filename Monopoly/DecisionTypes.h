// DecisionTypes.h
#pragma once

class Player;
class PropertyTile;

//requests
struct RollDiceDecision
{
    Player* player;
};

struct BuyPropertyDecision
{
    Player* player;
    PropertyTile* property;
};

struct MortgagePropertyDecision
{
    Player* player;
   // int propertyId;        // chosen by player should be in the answer
    int requiredAmount;
    Player* creditor;      // may be null
};




//results
struct RollDiceResult {};

struct BuyPropertyResult
{
    bool accepted;
};

struct MortgageResult
{
    int propertyId;
};