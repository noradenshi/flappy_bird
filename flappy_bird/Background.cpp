#include "Background.h"

Background::Background(sf::Texture* _texture, sf::Vector2f _w_size, float _scale)
{
	padding *= _scale;
	bgSpeed *= _scale;

	for (auto& a : background)
	{
		a.setTexture(*_texture);
		bgScale = _w_size.y / a.getLocalBounds().height;
		a.setScale(bgScale, bgScale);
	}
	width = background[0].getGlobalBounds().width - background[0].getGlobalBounds().left;
	background[1].setPosition(background[0].getPosition().x + width - padding, 0);
	background_dim.setFillColor(sf::Color(0, 0, 0, 100));
	_w_size.x += 100.f * _scale;
	background_dim.setSize(_w_size);
	background_dim.setPosition(-50.f * _scale, 0.f);
}

void Background::update(float _deltaTime, float __gameSpeed)
{
	float temp = -bgSpeed * _deltaTime * __gameSpeed;
	background[0].move(temp, 0);
	background[1].move(temp, 0);

	for (int i = 0; i < 2; i++)
	{
		temp = background[i].getPosition().x + width;
		if (temp < 0)
		{
			if (i == 0) background[0].setPosition(background[1].getPosition().x + width - padding, 0);
			else background[1].setPosition(background[0].getPosition().x + width - padding, 0);
		}
	}
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(background[0]);
	target.draw(background[1]);
	target.draw(background_dim);
}