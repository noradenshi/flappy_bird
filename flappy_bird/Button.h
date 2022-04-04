#pragma once
#include <SFML/Graphics.hpp>

enum class State {
	Idle, Hover, Click,
};

class Button : public sf::Drawable
{
private:
	State state = State::Click;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f startPos;
	sf::FloatRect bounds;

public:
	Button() = default;
	void create(sf::Vector2f _pos, std::string _text, sf::Font* _font, float);
	void reset();
	void move(float);
	void setState(State);
	State getState();
	sf::FloatRect getBounds() { return bounds; }
	std::string getString() { return text.getString(); }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
};

class Buttons : public sf::Drawable
{
private:
	Button buttons[3];
	float padding = 50.f;
	bool isActive = false;
	sf::RectangleShape backgroundTemp;
	sf::FloatRect backgroundRect;
	bool isHover = false;
	
public:
	Buttons() = default;
	Buttons(sf::Vector2f, sf::Font*, float, sf::Vector2i);
	void setActive(bool _val) { isActive = _val; }
	void reset();
	void move(float);
	bool getHover();
	void checkCollisions(sf::Vector2f);
	std::string mouseClick();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};