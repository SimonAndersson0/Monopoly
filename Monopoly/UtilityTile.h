#pragma once
#include "PropertyTile.h"
class UtilityTile :
    public PropertyTile
{
    public:
        explicit UtilityTile(const std::string& name, int price, int rent)
            : PropertyTile(name, price, rent) {
        }


};

