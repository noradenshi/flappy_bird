#pragma once
#include <SFML/Graphics.hpp>

class Border : public sf::Drawable
{
private:
	sf::RectangleShape border;
	sf::FloatRect borderRect;

public:
	Border(sf::Vector2f, sf::Vector2f);
	sf::FloatRect getRect();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};