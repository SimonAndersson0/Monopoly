#pragma once
#include "ActionTile.h"
#include <string>

class Player; 
class GameManager;


class JailTile :
    public ActionTile
{
    public:
        explicit JailTile(const int& ID, const std::string& name) : ActionTile(ID,name) {}
		void onLand(Player& player, GameManager& game) override;
};

