#include "SFMLUI.h"
#include "Button.h"

#include "Player.h"
#include "PropertyTile.h"

SFMLUI::SFMLUI()
    : m_window(sf::VideoMode(800, 600), "Monopoly Test UI")
{
    m_font.loadFromFile("arial.ttf"); // put font next to exe
}

void SFMLUI::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        draw();
    }
}

// ---------- Logging ----------
void SFMLUI::addLog(const std::string& text)
{
    m_log.push_back(text);
    if (m_log.size() > 20)
        m_log.erase(m_log.begin());
}

// ---------- Observers ----------
void SFMLUI::onTurnStarted(const Player& player)
{
    addLog("--- " + player.getName() + "'s turn ---");
}

void SFMLUI::onDiceRolled(const Player& player, int total)
{
    addLog(player.getName() + " rolled " + std::to_string(total));
}

void SFMLUI::onPlayerMoved(const Player& player, const Tile& tile)
{
    addLog(player.getName() + " landed on " + tile.getName());
}

void SFMLUI::onMoneyChanged(const Player& player, int amount)
{
    addLog(player.getName() + " now has $" + std::to_string(amount));
}

void SFMLUI::onGameOver()
{
    addLog("GAME OVER");
}

void SFMLUI::onPropertyBought(const Player& player, const PropertyTile& property)
{
    addLog(player.getName() + " bought " + property.getName());
}

void SFMLUI::onBankruptcy(const Player& player)
{
    addLog(player.getName() + " went bankrupt!");
}

void SFMLUI::onPassGo(const Player& player)
{
    addLog(player.getName() + " passed GO");
}

void SFMLUI::onTradeProposed(const TradeOffer& trade)
{
    addLog(trade.proposer->getName() + " proposed a trade");
}

void SFMLUI::onMortgage(const Player& player, const PropertyTile& property)
{
    addLog(player.getName() + " mortgaged " + property.getName());
}

// ---------- Decisions ----------
void SFMLUI::onDecisionRequested(const Decision& decision)
{
    m_pendingDecision = decision;
    rebuildButtons();
}

// ---------- UI ----------
void SFMLUI::rebuildButtons()
{
    m_buttons.clear();

    if (!m_pendingDecision.has_value())
        return;

    std::visit([this](auto&& d)
        {
            using T = std::decay_t<decltype(d)>;

            if constexpr (std::is_same_v<T, RollDiceDecision>)
            {
                m_buttons.emplace_back(
                    sf::Vector2f(50, 500),
                    sf::Vector2f(200, 40),
                    "Roll Dice",
                    m_font,
                    [this]()
                    {
                        submitDecisionResult(RollDiceResult{});
                        m_pendingDecision.reset();
                        m_buttons.clear();
                    }
                );
            }
            else if constexpr (std::is_same_v<T, BuyPropertyDecision>)
            {
                m_buttons.emplace_back(
                    { 50, 500 }, { 200, 40 }, "Buy", m_font,
                    [this]()
                    {
                        submitDecisionResult(BuyPropertyResult{ true });
                        m_pendingDecision.reset();
                        m_buttons.clear();
                    }
                );
                m_buttons.emplace_back(
                    { 300, 500 }, { 200, 40 }, "Skip", m_font,
                    [this]()
                    {
                        submitDecisionResult(BuyPropertyResult{ false });
                        m_pendingDecision.reset();
                        m_buttons.clear();
                    }
                );
            }
            else if constexpr (std::is_same_v<T, MortgagePropertyDecision>)
            {
                // TEMP: mortgage first valid property automatically
                m_buttons.emplace_back(
                    { 50, 500 }, { 300, 40 }, "Mortgage First Property", m_font,
                    [this, &d]()
                    {
                        int id = d.player->getProperties().front()->getID();
                        submitDecisionResult(MortgageResult{ id });
                        m_pendingDecision.reset();
                        m_buttons.clear();
                    }
                );
            }
        }, *m_pendingDecision);
}

void SFMLUI::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        for (auto& b : m_buttons)
            b.handleEvent(event, m_window);
    }
}

void SFMLUI::draw()
{
    m_window.clear(sf::Color::Black);

    float y = 10.f;
    for (const auto& line : m_log)
    {
        sf::Text text(line, m_font, 16);
        text.setPosition(10.f, y);
        m_window.draw(text);
        y += 20.f;
    }

    for (auto& b : m_buttons)
        b.draw(m_window);

    m_window.display();
}
