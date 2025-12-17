#pragma once
#include "PropertyTile.h"
class RailroadTile :
    public PropertyTile
{
    public:
        explicit RailroadTile(const std::string& name, int price, int rent)
            : PropertyTile(name, price, rent)
		{
		}
        
};

