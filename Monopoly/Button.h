#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const std::string& text,
        sf::Font& font,
        std::function<void()> onClick
    );

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::function<void()> m_onClick;
};
