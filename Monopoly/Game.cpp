#include "Game.h"
#include <numeric>
#include <iostream>
#include "DecisionProvider.h"
#include "ConsoleDecisionProvider.h"
#include "BotDecisionProvider.h"
#include "Player.h"
#include "Board.h"
#include <thread>
#include <chrono>
#include "Decision.h"
#include "SFMLUI.h"

#include "GameManager.h"
#include "UI.h"
#include "Tile.h"
#include "SFMLDecisionProvider.h"
#include "DecisionTypes.h"

// Define destructor out-of-line so unique_ptr destructor is instantiated

Game::~Game() = default; //needed when unique_ptr is used in header or else compiler gives error since it tries to delete from header where the include is not known

Game::Game(const std::string& boardXmlPath, UI& ui)
    : m_board(boardXmlPath),
    m_gameManager(m_board),
    m_ui(ui)
{
}



//void Game::setupPlayers()
//{
//    int playerCount = m_ui.requestPlayerCount();
//
//    for (int i = 0; i < playerCount; ++i)
//    {
//        std::string name = m_ui.requestPlayerName(i);
//
//        bool isBot = m_ui.requestIsBot(name);
//
//        UI* uiForPlayer = &m_ui; // shared UI by default
//
//        std::unique_ptr<DecisionProvider> controller;
//
//        if (isBot)
//            controller = std::make_unique<BotDecisionProvider>();
//        else
//            controller = std::make_unique<ConsoleDecisionProvider>(*uiForPlayer);
//
//        m_players.emplace_back(name, 15000, *controller);
//        m_controllers.push_back(std::move(controller));
//    }
//}

void Game::setupPlayers()
{
    int playerCount = m_ui.requestPlayerCount();

    for (int i = 0; i < playerCount; ++i)
    {
        std::string name = m_ui.requestPlayerName(i);
        bool isBot = m_ui.requestIsBot(name);

		UI* uiForPlayer = &m_ui; // first player / host sfml UI

        std::unique_ptr<DecisionProvider> controller;

        if (isBot)
        {
            controller = std::make_unique<BotDecisionProvider>();
        }
        else
        {
            
            // Create new SFML UI for every player except player1
            if (i==0) {
               controller = std::make_unique<SFMLDecisionProvider>(*uiForPlayer);
            } else
            {
                auto sfmlUI = std::make_unique<SFMLUI>();

                uiForPlayer = sfmlUI.get();
                m_playerUIs.push_back(std::move(sfmlUI)); // keep alive

                controller = std::make_unique<SFMLDecisionProvider>(*uiForPlayer);
			}

        }

        m_players.emplace_back(name, 15000, *controller);
        m_controllers.push_back(std::move(controller));
    }
}


void Game::run()
{
    setupPlayers();
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

void Game::playTurn(Player& player)
{
    // Start the turn by requesting a roll
    m_gameManager.requestDecision(
        RollDiceDecision{ &player }
    );

    // Let the game manager  controllers resolve everything
    while (true)
    {
        // First, update all SFML decision providers to keep windows responsive
        for (auto& controller : m_controllers)
        {
            if (auto* sfml = dynamic_cast<SFMLDecisionProvider*>(controller.get()))
                sfml->update();
        }

        // If we're waiting for a decision, do nothing else
        if (m_gameManager.getState() == GameState::WaitingForDecision)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        // Execute queued actions (rent, buy property, etc.)
        if (m_gameManager.hasPendingActions())
        {
            m_gameManager.executeNextAction();
            continue;
        }

        // Nothing left to resolve, turn ends
        break;
    }
}

