#pragma once
#include <vector>
#include <string>
#include "Dice.h"

class Player;

class GameManager
{
public:
    GameManager(int boardSize, int diceAmount = 2, int diceMaxValue = 6);

    // ---- Player movement ----
    void movePlayer(Player& player, int steps);

    // ---- Dice rolls ----
    std::vector<int> rollDice();   // returns individual dice
    int rollDiceTotal();           // returns total of dice

    int getBoardSize() const;

private:
    int m_boardSize;

    // Dice owned by the game manager
    Dice m_dice;
};
