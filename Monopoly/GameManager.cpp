#include "GameManager.h"
#include "Player.h"
#include "PropertyTile.h"
#include "Board.h"
#include "Tile.h"

// Constructor: initializes board size and dice
GameManager::GameManager(const Board& board, int diceAmount, int diceMaxValue)
    : m_board(board),
    m_dice(diceAmount, diceMaxValue)
{
}

// Move the player around the board
Tile* GameManager::movePlayer(Player& player) //might change to just math instead of each step if i dont wanna add midmove events ex rule when tile is passed
{
    int pos = player.getPosition();
    int steps = getSumOfLastRoll();
    int boardSize = m_board.getSize();

    while (steps > 0)
    {
        int toEnd = boardSize - pos;

        if (steps >= toEnd)
        {
            // We will pass (or land on) GO
            steps -= toEnd;
            pos = 0;

            giveMoney(player, 2000);
            // notify observers here if needed
        }
        else
        {
            pos += steps;
            steps = 0;
        }
    }

    player.setPosition(pos);
    return m_board.getTileAt(pos);
}

// Roll dice and return individual values
std::vector<int> GameManager::rollDice()
{
    m_lastRoll = m_dice.roll();
    return m_lastRoll;
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
        property.setOwner(&player);
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
    const std::vector<PropertyTile*>& properties = player.getProperties();

    if (creditor)
    {
        // give properties to creditor
        for (PropertyTile* property : properties) {
            player.removeProperty(*property);
            property->setOwner(creditor);
            creditor->addProperty(*property);
		}

    }
    else {
        // return properties to bank
        for (PropertyTile* property : properties) {
            player.removeProperty(*property);
            property->setOwner(nullptr);
		}
	}

}
bool GameManager::canMortgage(const Player& player, const PropertyTile& property) const{
    // Check if the player owns the property and if it's not already mortgaged
    return player.owns(property) && !property.isMortgaged();
}

int GameManager::getSumOfLastRoll() const{
    int sum = 0;
    for (int roll : m_lastRoll) {
        sum += roll;
    }
    return sum;
}

bool GameManager::isGameOver(const std::vector<Player> Players) const {
    int activePlayers = 0;
    for (const Player& player : Players) {
        if (!player.isBankrupt()) {
            activePlayers++;
        }
    }
    return activePlayers <= 1;
}


//maybe centralize rent calcu here