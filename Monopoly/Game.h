#pragma once

#include "Board.h"
#include "GameManager.h"
#include "Player.h"
#include "UI.h"
#include "Tile.h"

#include <vector>
#include <string>

enum class TurnState
{
    WaitingForRoll,
    Resolving,
    Auktioning,
    BuyingProperty,
    EndTurn
};

class Game
{
public:
    // Game owns the board and game manager, uses UI
    Game(const std::string& boardXmlPath, UI& ui);

    // Starts the main game loop
    void run();

private:
    void setupPlayers();
    void playTurn(Player& player);
	void setTurnState(TurnState newState);

    // Core systems
	bool m_gameIsOn = true;
    Board m_board;
    GameManager m_gameManager;
    UI& m_ui;

    // Players
    std::vector<Player> m_players;
    int m_currentPlayerIndex = 0;

    // Turn state
    TurnState m_turnState = TurnState::WaitingForRoll;
};
