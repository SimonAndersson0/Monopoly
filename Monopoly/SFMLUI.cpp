#include "SFMLUI.h"
#include "Player.h"
#include "Tile.h"
#include "PropertyTile.h"
#include "Decision.h"

#include <iostream>

// ------------------------------------------------------------

SFMLUI::SFMLUI(const std::string& title)
    : m_window(sf::VideoMode({ 700, 700 }), title)
{
    if (!m_font.openFromFile("Resources/ARIAL.TTF"))
        std::cerr << "Failed to load font\n";

    m_yesBtn.setSize({ 120.f, 40.f });
    m_noBtn.setSize({ 120.f, 40.f });

    m_yesBtn.setPosition({ 180.f, 500.f });
    m_noBtn.setPosition({ 380.f, 500.f });

    m_yesBtn.setFillColor(sf::Color(70, 130, 180));
    m_noBtn.setFillColor(sf::Color(120, 120, 120));

    m_yesText.setFont(m_font);
    m_noText.setFont(m_font);

    m_yesText.setString("Yes");
    m_noText.setString("No");

    m_yesText.setCharacterSize(16);
    m_noText.setCharacterSize(16);

    m_yesText.setPosition({ 220.f, 510.f });
    m_noText.setPosition({ 420.f, 510.f });

    pushMessage("SFML UI ready");
}

SFMLUI::~SFMLUI()
{
    if (m_window.isOpen())
        m_window.close();
}

// ------------------------------------------------------------

bool SFMLUI::isOpen() const
{
    return m_window.isOpen();
}

void SFMLUI::markDirty()
{
    m_dirty = true;
}

void SFMLUI::pushMessage(const std::string& msg)
{
    m_log.push_back(msg);
    if (m_log.size() > 12)
        m_log.erase(m_log.begin());

    markDirty();
}

// ------------------------------------------------------------
// Engine-style update
// ------------------------------------------------------------

void SFMLUI::poll()
{
    while (const std::optional ev = m_window.pollEvent())
    {
        if (ev->is<sf::Event::Closed>())
            m_window.close();

        if (!m_showYesNo)
            continue;

        if (auto mouse = ev->getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f p(
                static_cast<float>(mouse->position.x),
                static_cast<float>(mouse->position.y)
            );

            if (m_yesBtn.getGlobalBounds().contains(p))
            {
                m_yesNoAnswer = true;
                m_showYesNo = false;
                markDirty();
            }
            else if (m_noBtn.getGlobalBounds().contains(p))
            {
                m_yesNoAnswer = false;
                m_showYesNo = false;
                markDirty();
            }
        }
    }
}

void SFMLUI::render()
{
    if (!m_dirty)
        return;

    m_window.clear(sf::Color(30, 30, 30));
    draw();
    m_window.display();

    m_dirty = false;
}

// ------------------------------------------------------------
// Drawing
// ------------------------------------------------------------

void SFMLUI::draw()
{
    drawLog();
    drawPrompt();
}

void SFMLUI::drawLog()
{
    float y = 20.f;
    for (const auto& msg : m_log)
    {
        sf::Text t(m_font, msg, 14);
        t.setPosition({ 20.f, y });
        m_window.draw(t);
        y += 18.f;
    }
}

void SFMLUI::drawPrompt()
{
    if (!m_showYesNo)
        return;

    sf::Text prompt(m_font, m_promptText, 16);
    prompt.setPosition({ 20.f, 460.f });
    m_window.draw(prompt);

    m_window.draw(m_yesBtn);
    m_window.draw(m_noBtn);
    m_window.draw(m_yesText);
    m_window.draw(m_noText);
}

// ------------------------------------------------------------
// Observer callbacks
// ------------------------------------------------------------

void SFMLUI::onTurnStarted(const Player& p)
{
    pushMessage("--- " + p.getName() + "'s turn ---");
}

void SFMLUI::onDiceRolled(const Player& p, int total)
{
    pushMessage(p.getName() + " rolled " + std::to_string(total));
}

void SFMLUI::onPlayerMoved(const Player& p, const Tile& t)
{
    pushMessage(p.getName() + " landed on " + t.getName());
}

void SFMLUI::onMoneyChanged(const Player& p, int amt)
{
    pushMessage(p.getName() + " now has $" + std::to_string(amt));
}

void SFMLUI::onGameOver()
{
    pushMessage("Game Over");
}

void SFMLUI::onPropertyBought(const Player& p, const PropertyTile& prop)
{
    pushMessage(p.getName() + " bought " + prop.getName());
}

void SFMLUI::onBankruptcy(const Player& p)
{
    pushMessage(p.getName() + " is bankrupt");
}

void SFMLUI::onPassGo(const Player& p)
{
    pushMessage(p.getName() + " passed GO");
}

void SFMLUI::onDecisionRequested(const Decision&)
{
    pushMessage("Decision requested");
}

// ------------------------------------------------------------
// UI input (non-blocking)
// ------------------------------------------------------------

void SFMLUI::waitForRoll(const Player& p)
{
    pushMessage(p.getName() + ": roll dice requested");
}

bool SFMLUI::requestBuyProperty(const Player& p, const PropertyTile& prop)
{
    m_promptText = p.getName() + ", buy " + prop.getName() + "?";
    m_showYesNo = true;
    m_yesNoAnswer.reset();
    markDirty();
    return false;
}

int SFMLUI::requestMortgageProperty(const Player&)
{
    pushMessage("Mortgage UI not implemented");
    return -1;
}

bool SFMLUI::hasYesNoAnswer() const
{
    return m_yesNoAnswer.has_value();
}

bool SFMLUI::consumeYesNoAnswer()
{
    bool v = *m_yesNoAnswer;
    m_yesNoAnswer.reset();
    return v;
}
