#pragma once
#include "ActionTile.h"
#include <string>

class Player;
class GameManager;

class GoTile :
    public ActionTile
{
public:
        explicit GoTile(const int& ID, std::string& name)
            : ActionTile(ID,name) {
        }
		void onLand(Player& player, GameManager& game) override;
};

