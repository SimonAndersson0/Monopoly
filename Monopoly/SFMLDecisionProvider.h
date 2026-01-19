#pragma once
#include "DecisionProvider.h"
#include <functional>

class SFMLUI;
class Player;
class PropertyTile;

class SFMLDecisionProvider : public DecisionProvider
{
public:
    explicit SFMLDecisionProvider(SFMLUI& ui);

    void update(); // called every frame

    void waitForRoll(Player&, std::function<void()> onRolled) override;
    void decideBuyProperty(Player&, PropertyTile&, std::function<void(bool)> onDecided) override;
    void decideMortgageProperty(Player&, int, std::function<void(int)>) override;

private:
    SFMLUI& m_ui;
    std::function<void(bool)> m_pendingYesNo;
};
