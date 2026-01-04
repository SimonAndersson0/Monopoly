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
    m_gameManager(m_board.getSize()),
    m_ui(ui)
{
}

void Game::run()
{
    setupPlayers();

    while (m_gameIsOn) // add proper game-over logic later
    {
        Player& currentPlayer = m_players[m_currentPlayerIndex];
        m_ui.showMessage("\n--- " + currentPlayer.getName() + "'s turn ---");

        playTurn(currentPlayer);

        // Advance to next player
        m_currentPlayerIndex =
            (m_currentPlayerIndex + 1) % m_players.size();
    }
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
    // ---- Roll dice ----
    player.controller().waitForRoll(player);

    std::vector<int> rolls = m_gameManager.rollDice();
    int rollTotal = std::accumulate(rolls.begin(), rolls.end(), 0);

    std::string rollMsg = "Rolled: ";
    for (int r : rolls)
        rollMsg += std::to_string(r) + " ";
    rollMsg += "(Total: " + std::to_string(rollTotal) + ")";
    m_ui.showMessage(rollMsg);

    // ---- Move player ----
    int oldPosition = player.getPosition();
    int boardSize = m_board.getSize();
    int newPosition = (oldPosition + rollTotal) % boardSize;

    if (oldPosition + rollTotal >= boardSize)
    {
        if (m_gameManager.giveMoney(player, 200))
            m_ui.showMessage(player.getName() + " passed GO and received 200!");
    }

    player.setPosition(newPosition);

    Tile* tile = m_board.getTileAt(newPosition);
    m_ui.showMessage("You have: " + std::to_string(player.getMoney()));
    m_ui.showMessage("Landed on: " + tile->getName());

    tile->onLand(player, m_gameManager);

    while (m_gameManager.hasPendingActions())
    {
        m_gameManager.executeNextAction();
    }
}
