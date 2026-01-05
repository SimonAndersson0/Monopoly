#include "Game.h"
#include <numeric>
#include <iostream>
#include "DecisionProvider.h"
#include "ConsoleDecisionProvider.h"
#include "BotDecisionProvider.h"

// Define destructor out-of-line so unique_ptr destructor is instantiated

Game::~Game() = default; //needed when unique_ptr is used in header or else compiler gives error since it tries to delete from header where the include is not known

Game::Game(const std::string& boardXmlPath, UI& ui)
    : m_board(boardXmlPath),
    m_gameManager(m_board),
    m_ui(ui)
{
}

void Game::run()
{
    setupPlayers();

    while (!m_gameManager.isGameOver(m_players)) // add proper game-over logic later
    {
        Player& currentPlayer = m_players[m_currentPlayerIndex];
        m_ui.showMessage("\n--- " + currentPlayer.getName() + "'s turn ---");

        if (!currentPlayer.isBankrupt())
        {
            playTurn(currentPlayer);
		}
        else {
            m_ui.showMessage(currentPlayer.getName() + " is bankrupt and skipped.");
        }
        
        // Advance to next player
        m_currentPlayerIndex =
            (m_currentPlayerIndex + 1) % m_players.size();
    }
	m_ui.showMessage("Game Over!");
}

void Game::setupPlayers()
{
    int playerCount = m_ui.askInt("Enter number of players:");

    for (int i = 0; i < playerCount; ++i)
    {
        std::string name = m_ui.askString(
            "Enter name for player " + std::to_string(i + 1) + ":"
        );

        bool yesIsABot = m_ui.askYesNo("Is this player a bot?");

        std::unique_ptr<DecisionProvider> controller;

        if (yesIsABot)
            controller = std::make_unique<BotDecisionProvider>();
        else
            controller = std::make_unique<ConsoleDecisionProvider>(m_ui);

        // Create player with controller
        m_players.emplace_back(name, 1500, *controller);

        // Store controller so it stays alive
        m_controllers.push_back(std::move(controller));
    }
}

void Game::playTurn(Player& player)
{
    player.controller().waitForRoll(player);

    m_gameManager.rollDice();

    int rollTotal = m_gameManager.getSumOfLastRoll();

    m_ui.showMessage("Rolled " + std::to_string(rollTotal));

    // RULE: movement & pass-go handled here
    Tile* landedTile = m_gameManager.movePlayer(player);

    m_ui.showMessage("You have: " + std::to_string(player.getMoney()));

    if (landedTile)
    {
        m_ui.showMessage("Landed on: " + landedTile->getName());
        landedTile->onLand(player, m_gameManager);
    }
    else
    {
        // This should never happen if board is valid otherwise something is very wrong with the tile indexing or the board itself was not built correctly
        m_ui.showMessage("Error: landed on an invalid tile!");
    }

    while (m_gameManager.hasPendingActions())
    {
        m_gameManager.executeNextAction();
    }
}
