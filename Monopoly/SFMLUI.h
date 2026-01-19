#pragma once
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <optional>

struct TradeOffer;
class Player;
class Tile;
class PropertyTile;



class SFMLUI : public UI
{
public:
    SFMLUI();
    ~SFMLUI() override;

    // GameObserver
    void onTurnStarted(const Player& player) override;
    void onDiceRolled(const Player& player, int total) override;
    void onPlayerMoved(const Player& player, const Tile& tile) override;
    void onMoneyChanged(const Player& player, int newAmount) override;
    void onGameOver() override;
    void onPropertyBought(const Player& player, const PropertyTile& property) override;
    void onBankruptcy(const Player& player) override;
    void onPassGo(const Player& player) override;
    void onDecisionRequested(const Decision& decision) override;
    void onTradeProposed(const TradeOffer& trade) override;
    void onMortgage(const Player& player, const PropertyTile& property) override;

    // UI (input)
    void waitForRoll(const Player& player) override;
    bool requestBuyProperty(const Player& player, const PropertyTile& property) override;
    int requestMortgageProperty(const Player& player) override;

    int requestPlayerCount() override;
    std::string requestPlayerName(int index) override;
    bool requestIsBot(const std::string& playerName) override;

private:
    // Simple button helper
    struct Button
    {
        sf::RectangleShape rect;
        sf::Text text;
        Button() = default;
        Button(const sf::Font& font) : text(font) {}
        sf::FloatRect bounds() const { return rect.getGlobalBounds(); }
        bool contains(const sf::Vector2f& p) const { return bounds().contains(p); }
    };

    void pushMessage(const std::string& msg);
    void drawModal(const std::vector<Button>& buttons, const std::string& title);
    bool promptYesNo(const std::string& prompt);
    void waitContinue(const std::string& prompt);

    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_fontLoaded = false;

    std::vector<std::string> m_log; // recent messages
    const unsigned m_windowW = 700;
    const unsigned m_windowH = 700;
};
