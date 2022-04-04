#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Pipe : public sf::Drawable
{
private:
	sf::Sprite topPipeEnd;
	sf::Sprite bottomPipeEnd;
	sf::RectangleShape topPipeBase;
	sf::RectangleShape bottomPipeBase;
	std::vector<sf::FloatRect> pipeRect;
	sf::Color color = sf::Color(60, 45, 46, 255);
	//sf::Color color = sf::Color(38, 28, 29, 255);
	//sf::Color color = sf::Color(83, 68, 70, 255);
	float gap = 100.f;
	bool isActive = false;
	bool isOutOfBounds = false;
	bool isOutOfBoundsRight = false;
	sf::Vector2f startPos;

	sf::Sprite point;
	int points = 1;
	bool isTaken = false;
	sf::Sound sound;
	sf::SoundBuffer pointBuffer;

	bool doReset = false;

public:
	void initialize(sf::Vector2f, sf::Texture*, sf::Texture*, float);
	void create(float);
	void move(float);
	void reset() { doReset = true; }
	void setActive(bool);
	bool getActive() { return isActive; }
	bool getOutOfBounds();
	std::vector<sf::FloatRect> getRect();
	int getPoints(int);
	bool getBoundsRight();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

class Pipes
{
private:
	const int bufforSize = 10;
	int nextPipe = 0;
	int firstPipe = 0;
	float speed = 160.f;
	bool doMove = false;
	bool doReset = false;
	
public:
	Pipe buffor[10];
	Pipes(sf::Vector2f, sf::Texture*, sf::Texture*, float);
	void update(float, float);
	void create(float);
	void reset();
	void setMove(bool _val) { doMove = _val; }
	void clear();
};