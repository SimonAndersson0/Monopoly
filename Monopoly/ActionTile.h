#pragma once
#include "Tile.h"
class ActionTile :
    public Tile
{
    public:
		explicit ActionTile(const std::string& name) : Tile(name) {}

};

