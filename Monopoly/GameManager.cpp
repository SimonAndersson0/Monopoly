#include "GameManager.h"
#include "GameObserver.h"
#include "Player.h"
#include "PropertyTile.h"
#include "Board.h"
#include "Tile.h"
#include "PayMoneyAction.h"
#include "TradeOffer.h"
#include "Decision.h"
#include "DecisionProvider.h"

//think these are needed for dynamic cast // check tile type when calculating rent
#include "UtilityTile.h"
#include "StreetTile.h"
#include "railroadTile.h"

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

            giveMoney(player, 200);
            for (auto* obs : m_observers)
				obs->onPassGo(player);
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

//action
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

//observers
void GameManager::addObserver(GameObserver* observer)
{
    m_observers.push_back(observer);
}
void GameManager::removeObserver(GameObserver* observer)
{
    m_observers.erase(
        std::remove(
            m_observers.begin(),
            m_observers.end(),
            observer
        ),
        m_observers.end()
    );
}

int GameManager::calculateRent(const PropertyTile& property) const{
    return property.calculateRent(*this);
}


void GameManager::chargeRent(Player& tenant, PropertyTile& property){
    Player* owner = property.getOwner();
    if (owner && owner != &tenant && !property.isMortgaged()) {
        int rent = calculateRent(property);
        queueAction(std::make_unique<PayMoneyAction>(tenant, rent, owner));
    }
}

   

int GameManager::countOwnedUtilities(const Player& player) const
{
    int count = 0;

    for (const auto& tilePtr : m_board.getTiles())
    {
        const Tile* tile = tilePtr.get();

        // Check if this tile is a UtilityTile
        const UtilityTile* utility =
            dynamic_cast<const UtilityTile*>(tile);

        if (!utility)
            continue;

        // Check ownership
        if (utility->getOwner() == &player)
            ++count;
    }

    return count;
}
int GameManager::countOwnedRailroads(const Player& player) const
{
    int count = 0;
    for (const auto& tilePtr : m_board.getTiles())
    {
        const Tile* tile = tilePtr.get();
        // Check if this tile is a RailroadTile
        const RailroadTile* railroad =
            dynamic_cast<const RailroadTile*>(tile);
        if (!railroad)
            continue;
        // Check ownership
        if (railroad->getOwner() == &player)
            ++count;
    }
    return count;
}
bool GameManager::doesPlayerOwnAllInSet(const Player& player, const PropertyTile& property) const
{
    // First, we need to determine the color set of the given property
    const StreetTile* streetProperty =
        dynamic_cast<const StreetTile*>(&property);
    if (!streetProperty)
        return 0; // Not a street property, so no color set
    std::string colorSet = streetProperty->getColorGroup();
    // Now, count how many properties in this color set the player owns
    int ownedCount = 0;
    int totalCount = 0;
    for (const auto& tilePtr : m_board.getTiles())
    {
        const Tile* tile = tilePtr.get();
        const StreetTile* streetTile =
            dynamic_cast<const StreetTile*>(tile);
        if (!streetTile)
            continue;
        if (streetTile->getColorGroup() == colorSet)
        {
            ++totalCount;
            if (streetTile->getOwner() == &player)
                ++ownedCount;
        }
    }
    return (ownedCount == totalCount);
}


//decisions
//SUBMIT
void GameManager::submitDecisionResult(const Decision& result)
{
    if (!m_pendingDecision)
        return;

    const Decision decision = *m_pendingDecision;

    switch (decision.type)
    {
    case Decision::Type::BuyProperty:
    {
        if (result.boolValue &&
            canAfford(*decision.player, decision.property->getPrice()))
        {
            buyProperty(*decision.player, *decision.property);
        }
        else
        {
            // later: start auction
        }
        break;
    }

    case Decision::Type::RollDice:
    {
        // Dice logic belongs here, NOT in provider
        m_lastRoll = m_dice.roll();

        for (auto* obs : m_observers)
            obs->onDiceRolled(*decision.player, getSumOfLastRoll());

        break;
    }
    case Decision::Type::MortgageProperty:
    {
        Tile* tile = m_board.getTileById(tileId);
        auto* property = dynamic_cast<PropertyTile*>(tile);

        if (!property || !canMortgage(*decision.player, *property))
        {
            // Ask again
            queueAction(std::make_unique<RaiseMoneyAction>(
                *decision.player,
                decision.requiredAmount,
                decision.creditor
            ));
        }
        else
        {
            mortgageProperty(*decision.player, *property);

            // Try again after mortgaging
            queueAction(std::make_unique<RaiseMoneyAction>(
                *decision.player,
                decision.requiredAmount,
                decision.creditor
            ));
        }
    }

    m_pendingDecision.reset();
    m_state = GameState::Free;
}

//REQUEST
void GameManager::requestDecision(const Decision& decision)
{
    m_pendingDecision = decision;
    m_state = GameState::WaitingForDecision;

    Player& player = *decision.player;
    DecisionProvider& controller = player.controller();

    switch (decision.type)
    {
    case Decision::Type::BuyProperty:
    {
        controller.decideBuyProperty(
            player,
            *decision.property,
            [this](bool accepted)
            {
                Decision result;
                result.type = Decision::Type::BuyProperty;
                result.boolValue = accepted;
                submitDecisionResult(result);
            });
        break;
    }

    case Decision::Type::RollDice:
    {
        controller.waitForRoll(
            player,
            [this]()
            {
                Decision result;
                result.type = Decision::Type::RollDice;
                submitDecisionResult(result);
            });
        break;
    }
    }

    for (auto* obs : m_observers)
        obs->onDecisionRequested(decision);
}


// Trade management
bool GameManager::canCommitTrades() const
{
    return m_state == GameState::Free
        || m_state == GameState::WaitingForDecision;
}
void GameManager::proposeTrade(const TradeOffer& trade)
{
    m_pendingTrades.push_back(trade);

    for (auto* obs : m_observers)
        obs->onTradeProposed(trade);
}
void GameManager::acceptTrade(size_t index, Player& who)
{
    auto& trade = m_pendingTrades[index];

    if (&who == trade.target)
        trade.targetAccepted = true;
}
void GameManager::processTrades()
{
    if (!canCommitTrades())
        return;

    for (auto it = m_pendingTrades.begin(); it != m_pendingTrades.end(); )
    {
        if (it->proposerAccepted && it->targetAccepted)
        {
            executeTrade(*it);
            it = m_pendingTrades.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
void GameManager::executeTrade(const TradeOffer& trade)
{
    //trade logic
    //for (auto* p : trade.giveProperties)
    //{
    //    trade.proposer->removeProperty(*p);
    //    trade.target->addProperty(*p);
    //    p->setOwner(trade.target);
    //}

    //for (auto* p : trade.receiveProperties)
    //{
    //    trade.target->removeProperty(*p);
    //    trade.proposer->addProperty(*p);
    //    p->setOwner(trade.proposer);
    //}

    //transferMoney(*trade.proposer, *trade.target, trade.giveMoney);
    //transferMoney(*trade.target, *trade.proposer, trade.receiveMoney);
}