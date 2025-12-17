#pragma once
#include "PropertyTile.h"
class StreetTile :
    public PropertyTile
{
    public:
        explicit StreetTile(const std::string& name, int price, int rent, const std::string& colorGroup, int houseCost)
            : PropertyTile(name, price, rent),
            m_colorGroup(colorGroup),
			m_houseCost(houseCost)
            {}
        std::string getColorGroup() const { return m_colorGroup; }

        void onLand(Player& player, GameManager& game) override;

    private:
		std::string m_colorGroup;
		int m_houseCost;
};

