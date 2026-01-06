#include "Player.h"
#include "DecisionProvider.h"
#include "PropertyTile.h"


#include <algorithm>
#include <stdexcept>

// ---- Construction ----

Player::Player(std::string name, int startMoney, DecisionProvider& controller)
    : m_name(std::move(name))
    , m_money(startMoney)
    , m_controller(controller)
{
}

DecisionProvider& Player::controller()
{
    return m_controller;
}

// ---- Identity ----

const std::string& Player::getName() const
{
    return m_name;
}

// ---- Money ----

int Player::getMoney() const
{
    return m_money;
}

void Player::payMoney(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("payMoney amount must be positive");

    m_money -= amount;

    if (m_money < 0)
    {
        m_money = 0;
    }
}

void Player::receiveMoney(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("receiveMoney amount must be positive");

    m_money += amount;
}

// ---- Board position ----

int Player::getPosition() const
{
    return m_position;
}

void Player::setPosition(int newPosition)
{
    if (newPosition < 0)
        throw std::invalid_argument("Position cannot be negative");

    m_position = newPosition;
}

// ---- Properties ----

void Player::addProperty(PropertyTile& property)
{
    if (!owns(property))
        m_properties.push_back(&property);
}


void Player::removeProperty(PropertyTile& property)
{
    auto it = std::find(m_properties.begin(),
        m_properties.end(),
        &property);

    if (it != m_properties.end())
        m_properties.erase(it);
}

bool Player::owns(const PropertyTile& property) const
{
    return std::find(m_properties.begin(),
        m_properties.end(),
        &property)
        != m_properties.end();
}

const std::vector<PropertyTile*>& Player::getProperties() const
{
    return m_properties;
}

// ---- Jail / State ----

bool Player::hasGetOutOfJailCard() const
{
    return m_hasGetOutOfJailCard;
}

void Player::giveGetOutOfJailCard()
{
    m_hasGetOutOfJailCard = true;
}

void Player::useGetOutOfJailCard()
{
    if (m_hasGetOutOfJailCard)
        m_hasGetOutOfJailCard = false;
}

bool Player::isBankrupt() const
{
    return m_bankrupt;
}
int Player::calculateNetWorth() const
{
    int totalWorth = m_money;
    for (const PropertyTile* property : m_properties)
    {
        totalWorth += property->getPrice();
    }
    return totalWorth;
}

bool Player::isInJail() const {
    return m_inJail;
}
void Player::setInJail() {
	m_inJail = true;
}
void Player::realeseFromJail() {
    m_inJail = false;
}
void Player::declareBankruptcy() {
    m_bankrupt = true;
}