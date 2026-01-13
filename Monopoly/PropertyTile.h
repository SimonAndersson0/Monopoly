#pragma once
#include "Tile.h"
#include <string>
#include <vector>

class GameManager;
class Player; 

class PropertyTile :
    public Tile
{
    public:
        explicit PropertyTile(const std::string& name, int price, const std::vector<int>& rent) //constructor
            : Tile(name),
            m_price(price),
			m_rent(rent)
            {}
		virtual int getPrice() const { return m_price; }

		virtual std::vector<int> getRent() const { return m_rent; }

        void onLand(Player& player, GameManager& game) override;
		void setOwner(Player* player);
		Player* getOwner() const { return m_owner; }
		bool isMortgaged() const { return isMorgaged; }
		void setMortgaged(bool mortgaged) { isMorgaged = mortgaged; }
        virtual int calculateRent(const GameManager& game) const = 0;

    protected:
        int m_price;
        std::vector<int> m_rent;
        Player* m_owner = nullptr;
        bool isMorgaged = false;

    private: 
        
};

