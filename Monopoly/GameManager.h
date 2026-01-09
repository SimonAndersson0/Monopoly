#pragma once
#include <vector>
#include <string>
#include "Dice.h"
#include <queue>
#include <memory>
#include "Action.h"
#include "GameObserver.h"

class Player;
class PropertyTile;
class Board;
class Tile;

class GameManager
{
public:
    GameManager(const Board& board, int diceAmount = 2, int diceMaxValue = 6);

    // ---- Player movement ----
    Tile* movePlayer(Player& player);

    // ---- Dice rolls ----
    std::vector<int> rollDice(const Player& player);   // returns individual dice
	std::vector<int> getLastRoll() const { return m_lastRoll; }
    int getSumOfLastRoll() const;


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
    bool isGameOver(const std::vector<Player> Players) const;

    void addObserver(GameObserver* observer);
    void removeObserver(GameObserver* observer);
	const std::vector<GameObserver*>& getObservers() const { return m_observers; }

    int calculateRent(const PropertyTile& property) const;
    void chargeRent(Player& tenant, PropertyTile& property);
	int countOwnedUtilities(const Player& player) const;
	int countOwnedRailroads(const Player& player) const;


private:
    const Board& m_board;
	int m_totalMoney = 150000;
    std::queue<std::unique_ptr<Action>> m_actions;
    std::vector<int> m_lastRoll;
    // Dice owned by the game manager
    Dice m_dice;
    std::vector<GameObserver*> m_observers;
    
};
