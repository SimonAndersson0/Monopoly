// SFMLUI.h
#include <SFML/Graphics.hpp>

struct Button
{
    sf::RectangleShape rect;
    sf::Text text;

    explicit Button(const sf::Font& font)
        : text(font)
    {
    }

    bool contains(sf::Vector2f p) const
    {
        return rect.getGlobalBounds().contains(p);
    }
};