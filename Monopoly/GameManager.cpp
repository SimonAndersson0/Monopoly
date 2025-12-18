#include "GameManager.h"
#include "Player.h"

// Constructor: initializes board size and dice
GameManager::GameManager(int boardSize, int diceAmount, int diceMaxValue)
    : m_boardSize(boardSize),
    m_dice(diceAmount, diceMaxValue) // initialize dice here
{
}

// Move the player around the board
void GameManager::movePlayer(Player& player, int steps)
{
    // Assume Player has getPosition() and setPosition()
    int newPos = (player.getPosition() + steps) % m_boardSize;
    player.setPosition(newPos);
}

// Roll dice and return individual values
std::vector<int> GameManager::rollDice()
{
    return m_dice.roll();
}

// Roll dice and return total
int GameManager::rollDiceTotal()
{
    return m_dice.rollTotal();
}

int GameManager::getBoardSize() const
{
    return m_boardSize;
}

bool GameManager::giveMoney(Player& player, int amount) { //money alway goes through bank
    if (m_totalMoney >= amount) {
			m_totalMoney -= amount;
            player.receiveMoney(amount);
            return true;
        }
    return false;

}
bool GameManager::takeMoney(Player& player, int amount) { //money alway goes through bank
    if (m_totalMoney <= amount) {
        m_totalMoney += amount;
        player.payMoney(amount);
        return true;
    }
    return false;      
}
bool GameManager::canAfford(Player& player, int amount) {
    return player.getMoney() >= amount; //change to total money
}


