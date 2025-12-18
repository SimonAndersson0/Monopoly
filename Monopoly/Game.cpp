#include "Game.h"
#include <numeric>
#include <iostream>

Game::Game(const std::string& boardXmlPath, UI& ui)
    : m_board(boardXmlPath),
    m_gameManager(m_board.getSize()), // pass board size
    m_ui(ui)
{
}
void  Game::setTurnState(TurnState newState){
    // This function can be expanded later for additional logic on state change
    m_turnState = newState;
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
        m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.size();
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
        m_players.emplace_back(name, 1500);
    }
}

void Game::playTurn(Player& player)
{
    m_turnState = TurnState::WaitingForRoll;

    while (m_turnState != TurnState::EndTurn)
    {
        switch (m_turnState)
        {
        case TurnState::WaitingForRoll:
        {
            m_ui.waitForEnter("Press ENTER to roll dice...");

            // Roll dice via GameManager
            std::vector<int> rolls = m_gameManager.rollDice();
            int rollTotal = std::accumulate(rolls.begin(), rolls.end(), 0);

            // Show individual dice and total
            std::string rollMsg = "Rolled: ";
            for (int r : rolls) rollMsg += std::to_string(r) + " ";
            rollMsg += "(Total: " + std::to_string(rollTotal) + ")";
            m_ui.showMessage(rollMsg);

            // Move player
            int oldPosition = player.getPosition();
			int boardSize = m_board.getSize();
            int newPosition = (oldPosition + rollTotal) % boardSize;

            // Detect passing GO
            if (oldPosition + rollTotal >= boardSize)
            {
                if (m_gameManager.giveMoney(player, 200)) { //returns true on success
                    m_ui.showMessage(player.getName() + " passed GO and received 200!");
                }
                else {
                    m_ui.showMessage("Bank is out of money! Cannot pay GO bonus.");
                }
            }

            player.setPosition(newPosition);

            // Land on tile
            Tile* tile = m_board.getTileAt(newPosition);
            m_ui.showMessage("You have: " + std::to_string(player.getMoney()));
            m_ui.showMessage("Landed on: " + tile->getName());
            tile->onLand(player, m_gameManager);

			Game::setTurnState(TurnState::EndTurn);
            break;
        }

        case TurnState::EndTurn:
            break;
        }
    }
}
