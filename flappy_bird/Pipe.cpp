#include "Pipe.h"
//#include <iostream>

void Pipe::initialize(sf::Vector2f _pos, sf::Texture* _texture, sf::Texture* _iceCream_texture, float _scale)
{
	sf::FloatRect temp;
	startPos = _pos;

	gap *= _scale;

	topPipeEnd.setPosition(_pos.x, _pos.y - gap);
	topPipeEnd.setTexture(*_texture);
	topPipeEnd.setScale(5.f, 5.f);
	temp = topPipeEnd.getLocalBounds();
	topPipeEnd.setOrigin(temp.left + temp.width / 2, 0);
	topPipeEnd.setRotation(180.f);

	bottomPipeEnd.setPosition(_pos.x, _pos.y + gap);
	bottomPipeEnd.setTexture(*_texture);
	bottomPipeEnd.setScale(5.f, 5.f);
	temp = bottomPipeEnd.getLocalBounds();
	bottomPipeEnd.setOrigin(temp.left + temp.width / 2, 0);

	topPipeBase.setPosition(_pos.x, topPipeEnd.getPosition().y);
	topPipeBase.setFillColor(color);
	topPipeBase.setSize(sf::Vector2f(18.f, _pos.y));
	topPipeBase.setOrigin(18.f / 2, -9.f);
	topPipeBase.setScale(5.f, 5.f);
	topPipeBase.setRotation(180.f);

	bottomPipeBase.setPosition(_pos.x, bottomPipeEnd.getPosition().y);
	bottomPipeBase.setFillColor(color);
	bottomPipeBase.setSize(sf::Vector2f(18.f, _pos.y));
	bottomPipeBase.setOrigin(18.f / 2, -9.f);
	bottomPipeBase.setScale(5.f, 5.f);

	point.setPosition(_pos);
	point.setTexture(*_iceCream_texture);
	point.setScale(4.f , 4.f);
	sf::FloatRect tempRect = point.getLocalBounds();
	point.setOrigin(tempRect.width / 2, tempRect.height / 2);

	pointBuffer.loadFromFile("resources/sounds/point.wav");
	sound.setBuffer(pointBuffer);

	topPipeEnd.scale(_scale, _scale);
	topPipeBase.scale(_scale, _scale);
	bottomPipeEnd.scale(_scale, _scale);
	bottomPipeBase.scale(_scale, _scale);
	point.scale(_scale, _scale);
}

void Pipe::create(float _height)
{
	topPipeEnd.setPosition(startPos.x, _height - gap);
	bottomPipeEnd.setPosition(startPos.x, _height + gap);
	topPipeBase.setPosition(startPos.x, topPipeEnd.getPosition().y);
	bottomPipeBase.setPosition(startPos.x, bottomPipeEnd.getPosition().y);
	point.setPosition(startPos.x , _height);
	isTaken = false;
	isOutOfBounds = false;
	isOutOfBoundsRight = false;
	doReset = false;
}

void Pipe::move(float _amount)
{
	if (!isActive) return;
	
	topPipeEnd.move(_amount, 0.f);
	bottomPipeEnd.move(_amount, 0.f);
	topPipeBase.move(_amount, 0.f);
	bottomPipeBase.move(_amount, 0.f);
	point.move(_amount, 0.f);

	if (topPipeBase.getPosition().x < -150.f)
	{
		isActive = false;
		isOutOfBounds = true;
	}

	if (topPipeBase.getGlobalBounds().left > startPos.x)
	{
		isOutOfBoundsRight = true;
		isActive = false;
	}
}

void Pipe::setActive(bool value)
{
	isActive = value;
}

int Pipe::getPoints(int _score)
{
	if (!isTaken)
	{
		//if ((_score + 1) % 5 == 0) sound.setPitch(sound.getPitch() + .1f);
		//else sound.setPitch(0.8f);
		sound.setPitch(0.8f + _score % 5 / 20.f);
		sound.play();
	}
	isTaken = true;
	return points;
}

bool Pipe::getOutOfBounds()
{
	return isOutOfBounds; 
}
bool Pipe::getBoundsRight()
{
	return isOutOfBoundsRight;
}

std::vector<sf::FloatRect> Pipe::getRect()
{
	pipeRect.clear();
	if (doReset || !isActive) return pipeRect;
	pipeRect.push_back(topPipeEnd.getGlobalBounds());
	pipeRect.push_back(bottomPipeEnd.getGlobalBounds());
	pipeRect.push_back(topPipeBase.getGlobalBounds());
	pipeRect.push_back(bottomPipeBase.getGlobalBounds());
	if(!isTaken) pipeRect.push_back(point.getGlobalBounds());
	return pipeRect;
}

void Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isActive) return;
	target.draw(topPipeBase);
	target.draw(bottomPipeBase);
	target.draw(topPipeEnd);
	target.draw(bottomPipeEnd);
	if(!isTaken) target.draw(point);
}


Pipes::Pipes(sf::Vector2f _pos, sf::Texture* _texture, sf::Texture* _iceCream_texture, float _scale)
{
	speed *= _scale;

	for (int i = 0; i < bufforSize; i++)
	{
		buffor[i].initialize(_pos, _texture, _iceCream_texture,  _scale);
	}
}

void Pipes::update(float _deltaTime, float _gameSpeed)
{
	if (buffor[firstPipe].getOutOfBounds())
	{
		firstPipe++;
		if (firstPipe > bufforSize - 1) firstPipe = 0;
	}

	float temp = 0;
	if (doReset)
	{
		if (buffor[firstPipe].getBoundsRight())
		{
			firstPipe = nextPipe;
			doReset = false;
			clear();
			return;
		}
		temp = speed * _deltaTime * 20;
	}
	else if (doMove) temp = -(speed * _deltaTime * _gameSpeed);
	else return; 

	for (int i = 0; i < bufforSize; i++)
	{
		buffor[i].move(temp);
	}
}

void Pipes::create(float _height)
{
	if (doReset)
	{
		firstPipe = nextPipe;
		doReset = false;
		clear();
	}
	buffor[nextPipe].create(_height);
	buffor[nextPipe].setActive(true);
	nextPipe++;
	if (nextPipe > bufforSize-1) nextPipe = 0;
}

void Pipes::reset()
{
	doReset = true;
	for (int i = 0; i < bufforSize; i++)
	{
		buffor[i].reset();
	}
}

void Pipes::clear()
{
	for (int i = 0; i < bufforSize; i++)
	{
		buffor[i].setActive(false);
		//buffor[i].create(sf::Vector2f(1200.f, 0.f));
	}
}