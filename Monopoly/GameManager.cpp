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
#include "RaiseMoneyAction.h"
#include "BankruptcyAction.h"
#include <iostream>

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
    if (!canAfford(player, amount))
		return false;
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
    int playerNetworth = player.calculateNetWorth();

    if (playerNetworth <= amount) {  //player cannot raise enough money
        return false;
    }
    
    if (canAfford(player, amount)) {//player can afford with current money on hand
        return true;
    }
    //check if bank+ player money is enough to pay
    int missingAmount = amount - player.getMoney();

    //true if player and bank has enough money for player to be able to raise money
    return missingAmount <= getBankMoney();
           

}

void GameManager::mortgageProperty(Player& player, PropertyTile& property) {

	if (canMortgage(player, property)) {
        property.setMortgaged(true);
        giveMoney(player, property.getMortgageValue());
    }

    for (auto* obs : m_observers)
        obs->onMortgage(player, property);
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
void GameManager::submitDecisionResult(const DecisionResult& result)
{
    std::visit([this](auto&& r) //r is DecisionResult
        {
            using T = std::decay_t<decltype(r)>;

            if constexpr (std::is_same_v<T, BuyPropertyResult>)
            {
                const auto& decision =
                    std::get<BuyPropertyDecision>(*m_pendingDecision);

                if (r.accepted &&
                    canAfford(*decision.player,
                        decision.property->getPrice()))
                {
                    buyProperty(*decision.player, *decision.property);
                }
            }
            else if constexpr (std::is_same_v<T, RollDiceResult>)
            {
                const auto& decision =
                    std::get<RollDiceDecision>(*m_pendingDecision);

                Player& player = *decision.player;

                // 1. Roll dice (broadcasts event)
                rollDice(player);

                // 2. Move player
                Tile* landedTile = movePlayer(player);

                // 3. Trigger tile logic (THIS queues actions or decisions)
                landedTile->onLand(player, *this);
            }
            else if constexpr (std::is_same_v<T, MortgageResult>)
            {
                const auto& decision = std::get<MortgagePropertyDecision>(*m_pendingDecision); //get decision info
                //PROBLEM MIGHT BE THAT CANRAISEMONEY DONT CHECK IF BANK CAN GIVE THE PLAYER THE required amount 
                if (r.propertyId < 0)
                {
                    queueAction(
                        std::make_unique<BankruptcyAction>(
                            *decision.player,
                            decision.creditor
                        )
                    );
                    return;
                }
                Tile* tile = m_board.getTileById(r.propertyId);
                auto* property = dynamic_cast<PropertyTile*>(tile);
                if (property && canMortgage(*decision.player, *property))
                {
                    mortgageProperty(*decision.player, *property);
                }
                std::cout << "Mortgage resolved\n";
                // ontinue raising money if in dept
                if (decision.requiredAmount > 0 ) {
                    std::cout << "anotherpaymoneycreated resolved\n";
                    queueAction(
                        std::make_unique<PayMoneyAction>(
                            *decision.player,
                            decision.requiredAmount,
                            decision.creditor
                        )
                    );
                }


            }
        }, result);

    m_pendingDecision.reset();
    m_state = GameState::Free;
}

//REQUEST
void GameManager::requestDecision(const Decision & decision)
{
    m_pendingDecision = decision;
    m_state = GameState::WaitingForDecision;

    std::visit([this](auto&& d)
        {
            Player& player = *d.player;
            DecisionProvider& controller = player.controller();

            using T = std::decay_t<decltype(d)>;

            if constexpr (std::is_same_v<T, BuyPropertyDecision>)
            {
                controller.decideBuyProperty(
                    player,
                    *d.property,
                    [this](bool accepted)
                    {
                        submitDecisionResult(
                            BuyPropertyResult{ accepted }
                        );
                    }
                );
            }
            else if constexpr (std::is_same_v<T, RollDiceDecision>)
            {
                controller.waitForRoll(
                    player,
                    [this]()
                    {
                        submitDecisionResult(RollDiceResult{});
                    }
                );
            }
            else if constexpr (std::is_same_v<T, MortgagePropertyDecision>)
            {
                std::cout << "Mortgage decision requested\n";
                controller.decideMortgageProperty(
                    player,
                    d.requiredAmount,
                    [this](int propertyId)
                    {
                        submitDecisionResult(
                            MortgageResult{ propertyId }
                        );
                    }
                );
            }
        }, decision);

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