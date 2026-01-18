#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>

#include "Decision.h"
#include "TradeOffer.h"
#include "UI.h"
#include "GameObserver.h"

class Button;

class SFMLUI : public UI, public GameObserver {
public:
    SFMLUI();

    void run(); // main UI loop

    // ---- GameObserver ----
    void onTurnStarted(const Player& player) override;
    void onDiceRolled(const Player& player, int total) override;
    void onPlayerMoved(const Player& player, const Tile& tile) override;
    void onMoneyChanged(const Player& player, int amount) override;
    void onGameOver() override;
    void onPropertyBought(const Player& player, const PropertyTile& property) override;
    void onBankruptcy(const Player& player) override;
    void onPassGo(const Player& player) override;
    void onTradeProposed(const TradeOffer& trade) override;
    void onMortgage(const Player& player, const PropertyTile& property) override;
    void onDecisionRequested(const Decision& decision) override;

private:
    sf::RenderWindow m_window;
    sf::Font m_font;

    std::vector<std::string> m_log;
    std::vector<Button> m_buttons;

    std::optional<Decision> m_pendingDecision;

    void addLog(const std::string& text);
    void rebuildButtons();
    void processEvents();
    void draw();
};
