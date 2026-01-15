#pragma once
#include "Tile.h"
class ActionTile :
    public Tile
{
    public:
		explicit ActionTile(const int& ID, const std::string& name) : Tile(ID,name) {}

};

