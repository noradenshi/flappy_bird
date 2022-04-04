#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird : public sf::Drawable
{
private:
	//base
	sf::FloatRect birdLocalRect;
	sf::FloatRect birdRect;
	sf::FloatRect borderRect;
	float velocity = 0.f;
	float gravity = 500.f;
	float mass = 2.f;
	float flapForce = 400.f;
	float maxHeight = 0.f;
	bool death = false;
	bool hit = false;
	sf::CircleShape hitbox;
	sf::FloatRect hitboxRect;
	sf::Vector2f startPos;
	float scale;
	//vfx
	sf::Sprite bird;
	sf::IntRect frame[12];
	int currentFrame = 0;
	bool doAnimate = false;
	float nextFrame = .03f;
	float frameTimer = .0f;
	//sfx
	sf::Sound sound;
	sf::SoundBuffer flapBuffer, deathBuffer;

public:
	Bird(sf::Texture*, sf::Vector2f, sf::FloatRect, float);
	bool checkCollisions(std::vector<sf::FloatRect>);
	void update(float);
	void flap();
	bool isDead() { return death; }
	bool isHit() { return hit; }
	void reset();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};