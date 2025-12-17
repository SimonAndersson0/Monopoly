#pragma once
#include "ActionTile.h"
class FreeParkingTile :
    public ActionTile
{
    public:
        explicit FreeParkingTile(const std::string& name)
            : ActionTile(name) {}
		void onLand(Player& player, GameManager& game) override;
};

