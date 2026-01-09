#pragma once
#include "PropertyTile.h"
#include <vector>
#include <string>

class GameManager;

class StreetTile :
    public PropertyTile
{
    public:
        explicit StreetTile(const std::string& name, int price, const std::vector<int>& rent, const std::string& colorGroup, int houseCost)
            : PropertyTile(name, price, rent),
            m_colorGroup(colorGroup),
			m_houseCost(houseCost),
			m_maxHouses(4) //fix this
            {}
        std::string getColorGroup() const { return m_colorGroup; }

        //void onLand(Player& player, GameManager& game) override;
        //int getPrice() const override;
        //int getRent() const override;
		int getHouseCost() const { return m_houseCost; }
		int getHouses() const { return m_houses; }
		int getMaxHouses() const { return m_maxHouses; }
		bool hasHotel() const { return m_hasHotel; }
		void buildHouse() { if (m_houses < m_maxHouses) m_houses++; }
		void buildHotel() { if (m_houses == m_maxHouses) { m_houses = 0; m_hasHotel = true; } }
		int calculateRent(const GameManager& game) const override;
    private:
		std::string m_colorGroup;
		int m_houseCost;
		int m_houses = 0;
		int m_maxHouses;
		bool m_hasHotel = false;
};

