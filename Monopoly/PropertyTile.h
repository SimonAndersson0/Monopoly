#pragma once
#include "Tile.h"
class PropertyTile :
    public Tile
{
    public:
		explicit PropertyTile(const std::string& name, int price, int rent) //constructor
            : Tile(name),
            m_price(price),
			m_rent(rent)
            {}
		virtual int getPrice() const { return m_price; }
		virtual int getRent() const { return m_rent; }

    private:
		int m_price;
        int m_rent; 
};

