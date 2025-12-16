#pragma once

class Player;
class GameManager;

class Tile
{
public:
    virtual ~Tile() = default;
    virtual void onLand(Player& player, GameManager& game) = 0;
};

