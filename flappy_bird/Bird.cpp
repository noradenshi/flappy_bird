#include "Bird.h"

Bird::Bird(sf::Texture* _texture, sf::Vector2f _pos, sf::FloatRect _borderRect, float _scale)
{
	frame[0] = sf::IntRect(0, 0, 16, 9);
	frame[1] = sf::IntRect(32, 10, 16, 9);
	frame[2] = sf::IntRect(16, 10, 16, 9);
	frame[3] = sf::IntRect(0, 10, 16, 9);
	frame[4] = sf::IntRect(32, 0, 16, 9);
	frame[5] = sf::IntRect(16, 0, 16, 9);
	frame[6] = sf::IntRect(16, 0, 16, 9);
	frame[7] = sf::IntRect(16, 0, 16, 9);
	frame[8] = sf::IntRect(32, 0, 16, 9);
	frame[9] = sf::IntRect(0, 10, 16, 9);
	frame[10] = sf::IntRect(16, 10, 16, 9);
	frame[11] = sf::IntRect(32, 10, 16, 9);

	startPos = _pos;
	bird.setTexture(*_texture);
	bird.setTextureRect(frame[0]);
	bird.setScale(5.f, 5.f);
	birdLocalRect = bird.getLocalBounds();
	bird.setOrigin(birdLocalRect.left + birdLocalRect.width / 2, birdLocalRect.top + birdLocalRect.height / 2);
	bird.setPosition(_pos);
	borderRect = _borderRect;

	hitbox.setPosition(_pos);
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setRadius(5.f);
	hitboxRect = hitbox.getGlobalBounds();
	hitbox.setOrigin(hitboxRect.width / 2, hitboxRect.height / 2);

	deathBuffer.loadFromFile("resources/sounds/unsure.wav");
	flapBuffer.loadFromFile("resources/sounds/flap.wav");
	sound.setBuffer(flapBuffer);
	//sound.setPitch(1.1f);
	//sound.setVolume(80.f);
	
	//flapForce *= _scale;
	//gravity *= _scale;
	scale = _scale;
	bird.scale(_scale, _scale);
	hitbox.scale(_scale, _scale);
}

bool Bird::checkCollisions(std::vector<sf::FloatRect> _pipeRect)
{
	for (int i=0; i<_pipeRect.size(); i++)
	{
		if (hitboxRect.intersects(_pipeRect[i]))
		{
			if (i == 4) return true;
			hit = true;
			return false;
		}
	}
	return false;
}

void Bird::update(float _deltaTime)
{
	if (doAnimate)
	{
		frameTimer -= _deltaTime * 2;
		if (frameTimer < 0)
		{
			currentFrame++;
			if (currentFrame > 11)
			{
				currentFrame = 0;
				doAnimate = false;
			}
			bird.setTextureRect(frame[currentFrame]);
			frameTimer = nextFrame;
		}
	}
	if (velocity < gravity) velocity += gravity * mass * _deltaTime;
	bird.move(0.f, velocity * scale * _deltaTime);
	bird.setRotation((velocity / gravity) * 80);
	hitbox.setPosition(bird.getPosition());
	hitboxRect = hitbox.getGlobalBounds();
	if (hitboxRect.intersects(borderRect))
	{
		death = true;
		sound.setBuffer(deathBuffer);
		sound.setVolume(500.f);
		sound.play();
	}
}

void Bird::flap()
{
	if (!hit && bird.getPosition().y > maxHeight)
	{
		currentFrame = 0;
		frameTimer = nextFrame;
		doAnimate = true;
		sound.play();
		velocity = -flapForce;
	}
}

void Bird::reset()
{
	velocity = 0.f;
	death = false;
	hit = false;
	bird.setPosition(startPos);
	bird.setRotation(0.f);

	sound.setBuffer(flapBuffer);
	sound.setVolume(100.f);
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bird);
	//target.draw(hitbox);
}