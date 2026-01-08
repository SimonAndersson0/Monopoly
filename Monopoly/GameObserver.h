#pragma once

class Player;
class Tile;
class PropertyTile;

class GameObserver
{
public:
    virtual ~GameObserver() = default;

    virtual void onTurnStarted(const Player& player) = 0;
    virtual void onDiceRolled(const Player& player, int total) = 0;
    virtual void onPlayerMoved(const Player& player, const Tile& tile) = 0;
    virtual void onMoneyChanged(const Player& player, int newAmount) = 0;
    virtual void onGameOver() = 0;
    virtual void onPropertyBought(const Player&, const PropertyTile&) = 0;
    virtual void onBankruptcy(const Player&) = 0;

};
