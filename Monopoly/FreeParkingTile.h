#pragma once
#include "ActionTile.h"
#include <string>
class Player;
class GameManager;

class FreeParkingTile :
    public ActionTile
{
    public:
        explicit FreeParkingTile(const int& ID,const std::string& name)
            : ActionTile(ID,name) {}
		void onLand(Player& player, GameManager& game) override;
};

