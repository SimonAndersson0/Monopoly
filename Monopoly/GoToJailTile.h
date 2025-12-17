#pragma once
#include "ActionTile.h"
class GoToJailTile :
    public ActionTile
{
    public:
        explicit GoToJailTile(const std::string& name) : ActionTile(name) {}
		void onLand(Player& player, GameManager& game) override;
};

