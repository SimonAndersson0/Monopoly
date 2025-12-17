#pragma once
#include "ActionTile.h"
class JailTile :
    public ActionTile
{
    public:
        explicit JailTile(const std::string& name) : ActionTile(name) {}
		void onLand(Player& player, GameManager& game) override;
};

