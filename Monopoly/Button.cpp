#include "Button.h"

Button::Button(
    const sf::Vector2f& pos,
    const sf::Vector2f& size,
    const std::string& text,
    sf::Font& font,
    std::function<void()> onClick
)
    : m_onClick(onClick)
{
    m_shape.setPosition(pos);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(80, 80, 80));

    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(18);
    m_text.setFillColor(sf::Color::White);

    auto bounds = m_text.getLocalBounds();
    m_text.setPosition(
        pos.x + (size.x - bounds.width) / 2.f,
        pos.y + (size.y - bounds.height) / 2.f - 5.f
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse(
            window.mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y }
            )
        );

        if (m_shape.getGlobalBounds().contains(mouse)) {
            m_onClick();
        }
    }
}
