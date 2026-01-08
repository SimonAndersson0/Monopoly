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
Tile* GameManager::movePlayer(Player& player)
{
    int pos = player.getPosition();
    int steps = getSumOfLastRoll();
    int boardSize = m_board.getSize();

    while (steps > 0)
    {
        int toEnd = boardSize - pos;

        if (steps >= toEnd)
        {
            steps -= toEnd;
            pos = 0;
            giveMoney(player, 2000);
        }
        else
        {
            pos += steps;
            steps = 0;
        }
    }

    player.setPosition(pos);
    Tile* tile = m_board.getTileAt(pos);

    for (auto* obs : m_observers)
        obs->onPlayerMoved(player, *tile);

    return tile;
}


// Roll dice and return individual values
std::vector<int> GameManager::rollDice(const Player& player) //probably input player
{
    m_lastRoll = m_dice.roll(); //probably broadcast this instead

    int total = getSumOfLastRoll();
    // Dice roll is a public game event
    for (auto* obs : m_observers)
        obs->onDiceRolled(player, total);

    return m_lastRoll;
}


bool GameManager::giveMoney(Player& player, int amount)
{
    if (m_totalMoney >= amount)
    {
        m_totalMoney -= amount;
        player.receiveMoney(amount);

        for (auto* obs : m_observers)
            obs->onMoneyChanged(player, player.getMoney());

        return true;
    }
    return false;
}
bool GameManager::takeMoney(Player& player, int amount)
{
    m_totalMoney += amount;
    player.payMoney(amount);

    for (auto* obs : m_observers)
        obs->onMoneyChanged(player, player.getMoney());

    return true;
}
bool GameManager::canAfford(const Player& player, int amount) const{
    return player.getMoney() >= amount; 
}

void GameManager::buyProperty(Player& player, PropertyTile& property)
{
    if (canAfford(player, property.getPrice()))
    {
        takeMoney(player, property.getPrice());
        property.setOwner(&player);
        player.addProperty(property);

        for (auto* obs : m_observers)
            obs->onPropertyBought(player, property);
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
void GameManager::declareBankruptcy(Player& player, Player* creditor)
{
    player.declareBankruptcy();

    for (auto* obs : m_observers)
        obs->onBankruptcy(player);

    const auto& properties = player.getProperties();

    for (PropertyTile* property : properties)
    {
        player.removeProperty(*property);
        property->setOwner(creditor);

        if (creditor)
            creditor->addProperty(*property);
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

void GameManager::addObserver(GameObserver* observer)
{
    m_observers.push_back(observer);
}


//maybe centralize rent calcu here