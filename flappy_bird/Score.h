#pragma once
#include <SFML/Graphics.hpp>

class Score : public sf::Drawable
{
private:
	int score = 0;
	sf::Text text;
	sf::FloatRect textRect;

public:
	Score(sf::Font*, sf::Vector2f, float);
	void addScore(int);
	void setScore(int);
	int getScore();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};