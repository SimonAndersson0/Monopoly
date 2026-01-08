#include "ConsoleUI.h"
#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "PropertyTile.h"

void ConsoleUI::onTurnStarted(const Player& player)
{
    std::cout << "\n--- " << player.getName() << "'s turn ---\n";
}

void ConsoleUI::onDiceRolled(const Player& player, int total)
{
    std::cout << player.getName() << " rolled " << total << "\n";
}

void ConsoleUI::onPlayerMoved(const Player& player, const Tile& tile)
{
    std::cout << player.getName()
        << " landed on " << tile.getName() << "\n";
}

void ConsoleUI::onMoneyChanged(const Player& player, int amount)
{
    std::cout << player.getName()
        << " now has $" << amount << "\n";
}

void ConsoleUI::onGameOver()
{
    std::cout << "Game Over!\n";
}
