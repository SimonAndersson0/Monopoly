#pragma once
#include "ActionTile.h"
class GoTile :
    public ActionTile
{
public:
        explicit GoTile(const std::string& name)
            : ActionTile(name) {
        }
		void onLand(Player& player, GameManager& game) override;
};

