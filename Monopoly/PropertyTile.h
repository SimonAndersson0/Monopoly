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
		//virtual int getRent() const { return m_rent; }

        virtual int getRent() const = 0; //
        void onLand(Player& player, GameManager& game) override;
		void setOwner(Player& player);
		Player* getOwner() const { return m_owner; }
		bool isMortgaged() const { return isMorgaged; }
		void setMortgaged(bool mortgaged) { isMorgaged = mortgaged; }

    protected:
        int m_price;
        int m_rent; 
        Player* m_owner = nullptr;
        bool isMorgaged = false;

    private: 
        
};

