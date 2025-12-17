#pragma once

#include <string>
#include <vector>

class Player;
class Tile;
class Card;

class IGameUI
{
public:
    virtual ~IGameUI() = default;

    virtual void showMessage(const std::string& text) = 0;
    virtual void showPlayerStatus(const Player& player) = 0;

    virtual bool askYesNo(const std::string& question) = 0;
    virtual int askNumber(const std::string& question, int min, int max) = 0;

    virtual void showCard(const Card& card) = 0;
};
