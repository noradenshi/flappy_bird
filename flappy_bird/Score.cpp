#include "Score.h"

Score::Score(sf::Font* _font, sf::Vector2f _pos, float _scale)
{
	text.setFont(*_font);
	text.setCharacterSize(48 * _scale);
	text.setFillColor(sf::Color::White);
	text.setPosition(_pos);
}

void Score::addScore(int _amount)
{
	score += _amount;
	text.setString(std::to_string(score));
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}

void Score::setScore(int _amount)
{
	score = _amount;
	text.setString(std::to_string(score));
	if (score == 0) text.setString("");
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}

int Score::getScore()
{
	return score;
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}