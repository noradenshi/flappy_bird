#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::View view;
	float shakeDistance = 40.f;
	float shakeSpeed = 800.f;
	float fallSpeed = 100.f;
	bool doShake = false;
	bool doFall = false;
	bool doReset = false;
	int turns = 0;
	sf::Vector2f center;
	bool isReset = true;

public:
	Camera(sf::Vector2i, float);
	void shake();
	void fall();
	void update(sf::RenderWindow&, float);
	void reset(sf::RenderWindow&);
};