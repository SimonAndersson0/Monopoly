#include "SFMLUI.h"
#include "Player.h"
#include "Tile.h"
#include "PropertyTile.h"
#include "Decision.h"
#include "TradeOffer.h"

#include <iostream>

// ------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------

SFMLUI::SFMLUI()
    : m_window(
        sf::VideoMode({ m_windowW, m_windowH }),
        "Monopoly - SFML UI"
    )
{
    if (!m_font.openFromFile("Resources/ARIAL.TTF"))
    {
        std::cerr << "FAILED TO LOAD FONT\n";
        m_fontLoaded = false;
    }
    else
    {
        m_fontLoaded = true;
        std::cout << "Font loaded OK\n";
    }

    m_window.setKeyRepeatEnabled(false);

    m_window.setView(
        sf::View(sf::FloatRect(
            { 0.f, 0.f },
            { static_cast<float>(m_windowW), static_cast<float>(m_windowH) }
        ))
    );


    m_window.setSize({ m_windowW, m_windowH });

    pushMessage("SFML UI initialized");
}

SFMLUI::~SFMLUI()
{
    if (m_window.isOpen())
        m_window.close();
}

// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------

void SFMLUI::pushMessage(const std::string& msg)
{
    m_log.push_back(msg);
    if (m_log.size() > 8)
        m_log.erase(m_log.begin());
}

// ------------------------------------------------------------
// Drawing
// ------------------------------------------------------------

void SFMLUI::drawModal(const std::vector<Button>& buttons, const std::string& title)
{
    m_window.clear(sf::Color(30, 30, 30));

    
    // 
    // Title
    sf::Text titleText(m_font);

    titleText.setFont(m_font);
    titleText.setString(title);
    titleText.setCharacterSize(18);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 16.f, 16.f });
    m_window.draw(titleText);

    // Log
    float y = 48.f;
    for (const auto& msg : m_log)
    {
        sf::Text line(m_font);
        line.setFont(m_font);
        line.setString(msg);
        line.setCharacterSize(14);
        line.setFillColor(sf::Color(200, 200, 200));
        line.setPosition({ 16.f, y });
        m_window.draw(line);
        y += 18.f;
    }

    // Buttons
    for (const auto& b : buttons)
    {
        m_window.draw(b.rect);
        m_window.draw(b.text);
    }

    m_window.display();
}

// ------------------------------------------------------------
// UI Prompts
// ------------------------------------------------------------

bool SFMLUI::promptYesNo(const std::string& prompt)
{
    Button yes(m_font);
    yes.rect.setSize({ 120.f, 36.f });
    yes.rect.setPosition({ 100.f, 260.f });
    yes.rect.setFillColor(sf::Color(70, 130, 180));

    yes.text.setFont(m_font);
    yes.text.setString("Yes");
    yes.text.setCharacterSize(16);
    yes.text.setFillColor(sf::Color::White);
    yes.text.setPosition({ 136.f, 266.f });

    Button no(m_font);
    no.rect.setSize({ 120.f, 36.f });
    no.rect.setPosition({ 340.f, 260.f });
    no.rect.setFillColor(sf::Color(128, 128, 128));

    no.text.setFont(m_font);
    no.text.setString("No");
    no.text.setCharacterSize(16);
    no.text.setFillColor(sf::Color::White);
    no.text.setPosition({ 386.f, 266.f });

    std::vector<Button> buttons{ yes, no };
    drawModal(buttons, prompt);

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();

            if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f p{
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };

                    if (yes.contains(p)) return true;
                    if (no.contains(p)) return false;
                }
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Y) return true;
                if (key->code == sf::Keyboard::Key::N) return false;
                if (key->code == sf::Keyboard::Key::Escape) return false;
            }
        }

        drawModal(buttons, prompt);
    }

    return false;
}

void SFMLUI::waitContinue(const std::string& prompt)
{
    Button cont(m_font);
    cont.rect.setSize({ 200.f, 36.f });
    cont.rect.setPosition({ (m_windowW - 200.f) / 2.f, 260.f });
    cont.rect.setFillColor(sf::Color(70, 130, 180));

    cont.text.setFont(m_font);
    cont.text.setString("Continue (Enter)");
    cont.text.setCharacterSize(14);
    cont.text.setFillColor(sf::Color::White);
    cont.text.setPosition({ cont.rect.getPosition().x + 18.f, 266.f });

    std::vector<Button> buttons{ cont };
    drawModal(buttons, prompt);

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();

            if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f p{
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };
                    if (cont.contains(p)) return;
                }
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Enter ||
                    key->code == sf::Keyboard::Key::Space)
                    return;
            }
        }

        drawModal(buttons, prompt);
    }
}

// ------------------------------------------------------------
// GameObserver callbacks
// ------------------------------------------------------------

void SFMLUI::onTurnStarted(const Player& player)
{
    pushMessage("--- " + player.getName() + "'s turn ---");
}

void SFMLUI::onDiceRolled(const Player& player, int total)
{
    pushMessage(player.getName() + " rolled " + std::to_string(total));
}

void SFMLUI::onPlayerMoved(const Player& player, const Tile& tile)
{
    pushMessage(player.getName() + " landed on " + tile.getName());
}

void SFMLUI::onMoneyChanged(const Player& player, int newAmount)
{
    pushMessage(player.getName() + " now has $" + std::to_string(newAmount));
}

void SFMLUI::onGameOver()
{
    pushMessage("Game Over!");
    waitContinue("Game Over");
}

void SFMLUI::onPropertyBought(const Player& player, const PropertyTile& property)
{
    pushMessage(player.getName() + " bought " + property.getName());
}

void SFMLUI::onBankruptcy(const Player& player)
{
    pushMessage(player.getName() + " declared bankruptcy");
    waitContinue(player.getName() + " bankrupt");
}

void SFMLUI::onPassGo(const Player& player)
{
    pushMessage(player.getName() + " passed GO");
}

void SFMLUI::onDecisionRequested(const Decision&)
{
    pushMessage("Decision requested");
}

void SFMLUI::onTradeProposed(const TradeOffer&)
{
    pushMessage("Trade proposed");
}

void SFMLUI::onMortgage(const Player& player, const PropertyTile& property)
{
    pushMessage(player.getName() + " mortgaged " + property.getName());
}

// ------------------------------------------------------------
// UI Input
// ------------------------------------------------------------

void SFMLUI::waitForRoll(const Player& player)
{
    waitContinue(player.getName() + ", press Continue to roll dice");
}

bool SFMLUI::requestBuyProperty(const Player& player, const PropertyTile& property)
{
    return promptYesNo(
        player.getName() + ", buy " +
        property.getName() + " for $" +
        std::to_string(property.getPrice()) + "?"
    );
}

int SFMLUI::requestMortgageProperty(const Player& player)
{
    pushMessage("Mortgage not implemented for " + player.getName());
    waitContinue("Mortgage cancelled");
    return -1;
}

int SFMLUI::requestPlayerCount()
{
    waitContinue("Using default player count: 2");
    return 2;
}

std::string SFMLUI::requestPlayerName(int index)
{
    std::string name = "Player" + std::to_string(index + 1);
    pushMessage("Using player name: " + name);
    return name;
}

bool SFMLUI::requestIsBot(const std::string& playerName)
{
    return promptYesNo(playerName + " is a bot?");
}
