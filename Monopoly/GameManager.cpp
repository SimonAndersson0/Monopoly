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
