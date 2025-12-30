#pragma once
#include <vector>
#include <string>
#include "Dice.h"
#include <queue>
#include <memory>
#include "Action.h"

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
	bool giveMoney(Player& player, int amount);
	bool takeMoney(Player& player, int amount);
	bool canAfford(Player& player, int amount);
    void queueAction(std::unique_ptr<Action> action);
    bool hasPendingActions() const;
    void executeNextAction();


private:
    int m_boardSize;
	int m_totalMoney = 150000;
    std::queue<std::unique_ptr<Action>> m_actions;

    // Dice owned by the game manager
    Dice m_dice;
};
