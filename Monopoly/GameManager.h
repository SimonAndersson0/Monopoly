#pragma once
#include <vector>
#include <string>
#include "Dice.h"
#include <queue>
#include <memory>
#include "Action.h"

class Player;
class PropertyTile;

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
	bool canAfford(const Player& player, int amount) const;
    void queueAction(std::unique_ptr<Action> action);
    bool hasPendingActions() const;
    void executeNextAction();
    void buyProperty(Player& player, PropertyTile& property);
    void transferMoney(Player& from, Player& to, int amount);
    bool canRaiseMoney(const Player& player, int amount) const; //const after means it does not modify gamemanager
    void mortgageProperty(Player& player, PropertyTile& property);
    void declareBankruptcy(Player& player, Player* creditor);
	bool canMortgage(const Player& player, const PropertyTile& property) const;

private:
    int m_boardSize;
	int m_totalMoney = 150000;
    std::queue<std::unique_ptr<Action>> m_actions;

    // Dice owned by the game manager
    Dice m_dice;

    
};
