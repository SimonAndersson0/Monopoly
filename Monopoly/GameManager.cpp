#include "GameManager.h"
#include "Player.h"
#include "PropertyTile.h"

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
    if (true) {
        m_totalMoney += amount;
        player.payMoney(amount);
        return true;
    }
    return false;      
}
bool GameManager::canAfford(const Player& player, int amount) const{
    return player.getMoney() >= amount; 
}

void GameManager::buyProperty(Player& player, PropertyTile& property) {
    if (canAfford(player, property.getPrice())) {
        takeMoney(player, property.getPrice());
        property.setOwner(player);
        player.addProperty(property);
    }
}

void GameManager::queueAction(std::unique_ptr<Action> action)
{
    m_actions.push(std::move(action));
}

bool GameManager::hasPendingActions() const
{
    return !m_actions.empty();
}

void GameManager::executeNextAction()
{
    auto action = std::move(m_actions.front());
    m_actions.pop();
    action->execute(*this);
}

void GameManager::transferMoney(Player& from, Player& to, int amount){
    takeMoney(from, amount);
    giveMoney(to, amount);
}

bool GameManager::canRaiseMoney(const Player& player, int amount) const{
    return player.calculateNetWorth() >= amount;
}

void GameManager::mortgageProperty(Player&, PropertyTile&) {

}
void GameManager::declareBankruptcy(Player& player, Player* creditor) {
    //declare bankruptcy
    player.declareBankruptcy();
    //transfer properties/money to creditor if any
    

    if (creditor)
    {
        // give properties or money to creditor
    }
    else {
        // return properties to bank
	}

}
bool GameManager::canMortgage(const Player& player, const PropertyTile& property) const{
    // Check if the player owns the property and if it's not already mortgaged
    return player.owns(property) && !property.isMortgaged();
}