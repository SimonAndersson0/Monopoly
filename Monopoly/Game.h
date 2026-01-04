#pragma once

#include "Board.h"
#include "GameManager.h"
#include "Player.h"
#include "UI.h"
#include "Tile.h"

#include <vector>
#include <string>


class DecisionProvider;

class Game
{
public:
    // Game owns the board and game manager, uses UI
    Game(const std::string& boardXmlPath, UI& ui);
    ~Game(); // declare destructor out-of-line

    // Starts the main game loop
    void run();

private:
    void setupPlayers();
    void playTurn(Player& player);

    // Core systems
	bool m_gameIsOn = true;
    Board m_board;
    GameManager m_gameManager;
    UI& m_ui;

    // Players
    std::vector<Player> m_players;
    int m_currentPlayerIndex = 0;

    std::vector<std::unique_ptr<DecisionProvider>> m_controllers;
};
