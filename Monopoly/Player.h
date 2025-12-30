#pragma once

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class PropertyTile;
class DecisionProvider;

class Player
{
public:
    // ---- Construction ----
    Player(std::string name,
        int startMoney,
        DecisionProvider& controller);

    DecisionProvider& controller();

    // ---- Identity ----
    const std::string& getName() const;

    // ---- Money ----
    int getMoney() const;
    void payMoney(int amount);
    void receiveMoney(int amount);

    // ---- Board position ----
    int getPosition() const;
    void setPosition(int newPosition);

    // ---- Properties ----
    void addProperty(PropertyTile& property);
    void removeProperty(PropertyTile& property);
    bool owns(const PropertyTile& property) const;

    const std::vector<PropertyTile*>& getProperties() const;

    // ---- Jail / State ----
    bool hasGetOutOfJailCard() const;
    void giveGetOutOfJailCard();
    void useGetOutOfJailCard();

    bool isBankrupt() const;

    int calculateNetWorth() const;
    bool isInJail() const;
    void setInJail();
    void realeseFromJail();

private:
    // ---- Data ----
    std::string m_name;
    int m_money;
    DecisionProvider& m_controller;
    int m_position = 0;

    std::vector<PropertyTile*> m_properties;

    bool m_hasGetOutOfJailCard = false;
    bool m_bankrupt = false;
    bool m_inJail = false;

};