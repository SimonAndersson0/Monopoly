#pragma once
#include "PropertyTile.h"
#include <string>
#include <vector>

class GameManager;

class RailroadTile :
    public PropertyTile
{
    public:
        explicit RailroadTile(const int& ID, const std::string& name, int price, const std::vector<int>& rent)
            : PropertyTile(ID,name, price, rent)
		{
		}
     /*   int getPrice() const override;
        std::vector<int> getRent() const override;*/
        //void onLand(Player& player, GameManager& game) override;
        int calculateRent(const GameManager& game) const override;

    private:

        
};

