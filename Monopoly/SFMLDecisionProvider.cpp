#include "SFMLDecisionProvider.h"
#include "SFMLUI.h"
#include "Player.h"
#include "PropertyTile.h"

SFMLDecisionProvider::SFMLDecisionProvider(SFMLUI& ui)
    : m_ui(ui)
{
}

void SFMLDecisionProvider::update()
{
    m_ui.poll();
    m_ui.render();

    if (m_pendingYesNo && m_ui.hasYesNoAnswer())
    {
        bool answer = m_ui.consumeYesNoAnswer();
        auto cb = std::move(m_pendingYesNo);
        m_pendingYesNo = nullptr;
        cb(answer);
    }
}

void SFMLDecisionProvider::waitForRoll(Player&, std::function<void()> onRolled)
{
    onRolled(); // instant for now
}

void SFMLDecisionProvider::decideBuyProperty(
    Player&, PropertyTile&, std::function<void(bool)> onDecided)
{
    m_pendingYesNo = std::move(onDecided);
}

void SFMLDecisionProvider::decideMortgageProperty(
    Player&, int, std::function<void(int)>)
{
    // not implemented yet
}
