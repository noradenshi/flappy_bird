#include "Button.h"
#include <iostream>

void Button::create(sf::Vector2f _pos, std::string _text, sf::Font* _font, float _scale) {
	startPos = _pos;

	/*texture.loadFromFile("resources/tf.png");
	sprite.setTexture(texture);
	sprite.setTexture(texture);
	sprite.setOrigin(0, sprite.getGlobalBounds().height / 2);*/
	

	text.setString(_text);
	text.setFont(*_font);
	text.setCharacterSize(18 * _scale);
	text.rotate(-90);
	text.setOrigin(text.getGlobalBounds().height / 2, 0);
	//text.setFillColor(sf::Color::Black);
	bounds = text.getGlobalBounds();
	startPos.y += bounds.height / 2;
	state = State::Idle;
	reset();
	bounds = text.getGlobalBounds();
}

void Button::setState(State _state)
{
	state = _state;
	
	if (state == State::Hover)
	{
		text.setFillColor(sf::Color(220, 220, 220));
		text.setOutlineThickness(2.f);
	}
	else
	{
		text.setFillColor(sf::Color(255, 255, 255));
		text.setOutlineThickness(0.f);
	}

}

State Button::getState()
{ 
	return state; 
}

void Button::move(float _amount)
{
	sprite.move(_amount, 0.f);
	text.move(_amount, 0.f);
}

void Button::reset() { 
	sprite.setPosition(startPos); 
	text.setPosition(startPos); 
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates) const { 
	//target.draw(sprite); 
	target.draw(text); 
}

Buttons::Buttons(sf::Vector2f _pos, sf::Font* _font, float _scale, sf::Vector2i _w_size)
{
	buttons[0].create(_pos, "stats", _font, _scale);
	buttons[1].create(_pos += sf::Vector2f(0, buttons[0].getBounds().height + padding * _scale), "skins", _font, _scale);
	buttons[2].create(_pos += sf::Vector2f(0, buttons[1].getBounds().height + padding * _scale), "leaderboards", _font, _scale);

	backgroundTemp.setSize(sf::Vector2f(30.f * _scale, _w_size.y));
	backgroundTemp.setFillColor(sf::Color(200, 168, 171, 100));
	backgroundRect = backgroundTemp.getGlobalBounds();
}

void Buttons::checkCollisions(sf::Vector2f _mouse)
{
	if (!isActive) return;

	isHover = backgroundRect.contains(_mouse);
	if (!isHover) return;

	for (auto& a : buttons)
	{
		if (a.getBounds().contains(_mouse))
		{
			if (a.getState() == State::Idle)
			{
				a.setState(State::Hover);
			}
		}
		else
		{
			if (a.getState() != State::Idle)
			{
				a.setState(State::Idle);
			}
		}
	}
}

std::string Buttons::mouseClick()
{
	if (!isActive) return "";

	for (auto a : buttons)
	{
		if (a.getState() == State::Hover)
		{ 
			return a.getString();
		}
	}
	return "";
}

bool Buttons::getHover()
{
	if (!isActive) return false;

	return isHover;

	/*
	for (auto a : buttons)
		if (a.getState() == State::Hover)
			return true;
	return false;*/
}

void Buttons::move(float _amount)
{
	backgroundTemp.move(_amount, 0.f);
	for (auto& a : buttons)
		a.move(_amount);
}

void Buttons::reset()
{
	for (Button& b : buttons)
		b.reset();
}

void Buttons::draw(sf::RenderTarget& target, sf::RenderStates) const {
	if (!isActive) return;

	target.draw(backgroundTemp);
	for (Button b : buttons)
		target.draw(b);
}