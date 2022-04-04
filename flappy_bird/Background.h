#pragma once
#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
private:
	float padding = 1.f;
	float bgSpeed = 80.f;
	float bgScale;
	float width;
	sf::Sprite background[2];
	sf::RectangleShape background_dim;

public:
	Background(sf::Texture*, sf::Vector2f, float);
	void update(float, float);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};