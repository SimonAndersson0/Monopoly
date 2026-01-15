#pragma once
#include "ActionTile.h"
#include <string>

class Player;
class GameManager;


class GoToJailTile :
    public ActionTile
{
    public:
        explicit GoToJailTile(const int& ID, const std::string& name) : ActionTile(ID, name) {}
		void onLand(Player& player, GameManager& game) override;
};

