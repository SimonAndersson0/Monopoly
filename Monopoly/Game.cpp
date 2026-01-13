#include "Game.h"
#include <numeric>
#include <iostream>
#include "DecisionProvider.h"
#include "ConsoleDecisionProvider.h"
#include "BotDecisionProvider.h"
#include "Player.h"
#include "Board.h"

#include "GameManager.h"
#include "UI.h"
#include "Tile.h"

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

    // Register UI as observer ONCE
    m_gameManager.addObserver(&m_ui);

    while (!m_gameManager.isGameOver(m_players))
    {
        Player& player = m_players[m_currentPlayerIndex];


        if (!player.isBankrupt())
        {
            for (auto* obs : m_gameManager.getObservers())
                obs->onTurnStarted(player);

            playTurn(player);
        }

        m_currentPlayerIndex =
            (m_currentPlayerIndex + 1) % m_players.size();
    }

    for (auto* obs : m_gameManager.getObservers())
        obs->onGameOver();
}

void Game::setupPlayers()
{
    int playerCount = m_ui.requestPlayerCount();

    for (int i = 0; i < playerCount; ++i)
    {
        std::string name = m_ui.requestPlayerName(i);

        bool isBot = m_ui.requestIsBot(name);

        UI* uiForPlayer = &m_ui; // shared UI by default

        std::unique_ptr<DecisionProvider> controller;

        if (isBot)
            controller = std::make_unique<BotDecisionProvider>();
        else
            controller = std::make_unique<ConsoleDecisionProvider>(*uiForPlayer);

        m_players.emplace_back(name, 15000, *controller);
        m_controllers.push_back(std::move(controller));
    }
}

void Game::playTurn(Player& player)
{
    player.controller().waitForRoll(player);

    m_gameManager.rollDice(player);

    Tile* tile = m_gameManager.movePlayer(player);

    tile->onLand(player, m_gameManager);

    while (m_gameManager.hasPendingActions())
        m_gameManager.executeNextAction();
}
