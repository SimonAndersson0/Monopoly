#pragma once
#include "PropertyTile.h"
#include <vector>
#include <string>

class GameManager;

class UtilityTile :
    public PropertyTile
{
    public:
        explicit UtilityTile(const std::string& name, int price, const std::vector<int>& rent)
            : PropertyTile(name, price, rent) {
        }
        //void onLand(Player& player, GameManager& game) override;
        int calculateRent(const GameManager& game) const override;


};

