#pragma once
#include "PropertyTile.h"
class UtilityTile :
    public PropertyTile
{
    public:
        explicit UtilityTile(const std::string& name, int price, int rent)
            : PropertyTile(name, price, rent) {
        }
        //void onLand(Player& player, GameManager& game) override;
        int getPrice() const override;
        int getRent() const override;


};

