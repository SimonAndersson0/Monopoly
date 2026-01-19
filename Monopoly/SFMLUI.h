#pragma once
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <vector>

class Player;
class Tile;
class PropertyTile;
class Decision;

class SFMLUI : public UI
{
public:
    SFMLUI(const std::string& title);
    ~SFMLUI() override;

    // engine-style
    void poll();
    void render();
    bool isOpen() const;

    // GameObserver
    void onTurnStarted(const Player&) override;
    void onDiceRolled(const Player&, int) override;
    void onPlayerMoved(const Player&, const Tile&) override;
    void onMoneyChanged(const Player&, int) override;
    void onGameOver() override;
    void onPropertyBought(const Player&, const PropertyTile&) override;
    void onBankruptcy(const Player&) override;
    void onPassGo(const Player&) override;
    void onDecisionRequested(const Decision&) override;

    // UI input
    void waitForRoll(const Player&) override;
    bool requestBuyProperty(const Player&, const PropertyTile&) override;
    int requestMortgageProperty(const Player&) override;

    // non-blocking answer API
    bool hasYesNoAnswer() const;
    bool consumeYesNoAnswer();

private:
    void markDirty();
    void pushMessage(const std::string&);
    void draw();
    void drawLog();
    void drawPrompt();

    sf::RenderWindow m_window;
    sf::Font m_font;

    bool m_dirty = true;

    std::vector<std::string> m_log;

    // prompt state
    bool m_showYesNo = false;
    std::string m_promptText;
    std::optional<bool> m_yesNoAnswer;

    // buttons
    sf::RectangleShape m_yesBtn;
    sf::RectangleShape m_noBtn;
    sf::Text m_yesText;
    sf::Text m_noText;
};