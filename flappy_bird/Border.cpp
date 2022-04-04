#include "Border.h"

Border::Border(sf::Vector2f _size, sf::Vector2f _pos)
{
	_size.x += 100.f;
	border.setSize(_size);
	border.setOrigin(_size.x / 2, _size.y / 2 - 10.f);
	border.setPosition(_pos.x, _pos.y - _size.y/2);
	border.setFillColor(sf::Color(20, 20, 20, 255));

	borderRect = border.getGlobalBounds();
}

sf::FloatRect Border::getRect()
{
	return borderRect;
}

void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(border);
}