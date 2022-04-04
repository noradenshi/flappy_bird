#include "Profile.h"
#include <iostream>

Profile::Profile()
{
	std::cout << "profile object created\n";
}

Profile::Profile(sf::Font* _font, sf::Texture* _medalTexture, sf::IntRect _medalTextureRect[], float _scale)
{
	for (int i = 0; i < 6; i++) medalTextureRect[i] = _medalTextureRect[i];
	scale = _scale;

	//backgroundTexture.loadFromFile("resources/profile_bg.png");
	//backgroundSprite.setTexture(backgroundTexture);
	//backgroundSprite.scale(_scale, _scale);
	backgroundTemp.setSize(sf::Vector2f(380.f * _scale, 120.f * _scale));
	backgroundTemp.setFillColor(sf::Color(200, 168, 171, 100));
	backgroundRect = backgroundTemp.getGlobalBounds();

	avatarTexture.loadFromFile("resources/discord_logo.png");
	avatarTexture.setSmooth(true);
	avatarSprite.setTexture(avatarTexture);
	avatarScaleHelp = 50.f * _scale;
	float avatarScale = avatarScaleHelp / avatarSprite.getLocalBounds().width;
	avatarSprite.setScale(avatarScale, avatarScale);
	avatarSprite.setPosition(35.f * _scale, 12.f * _scale);
	startPos["avatarSprite"] = avatarSprite.getPosition();

	//avatarBackground.setSize(sf::Vector2f(55.f * _scale, 55.f * _scale));
	avatarBackground.setRadius(30.f * _scale);
	avatarBackground.setFillColor(sf::Color::White);
	avatarBackground.setOrigin(avatarBackground.getLocalBounds().width / 2, avatarBackground.getLocalBounds().height / 2);
	avatarBackground.setPosition(avatarSprite.getPosition().x + avatarSprite.getGlobalBounds().width / 2, avatarSprite.getPosition().y + avatarSprite.getGlobalBounds().height / 2);
	startPos["avatarBackground"] = avatarBackground.getPosition();

	nicknameText.setFont(*_font);
	nicknameText.setCharacterSize(28 * _scale);
	nicknameText.setPosition(avatarSprite.getPosition().x + avatarSprite.getGlobalBounds().width + 10.f * _scale, avatarSprite.getPosition().y + 1.f * _scale);
	startPos["nicknameText"] = nicknameText.getPosition();

	medalSprite.setTexture(*_medalTexture);
	medalSprite.setScale(2.f * _scale, 2.f * _scale);
	medalSprite.setPosition(avatarSprite.getPosition().x + 2.f * _scale, avatarSprite.getPosition().y + avatarSprite.getGlobalBounds().height + 8.f * _scale);
	startPos["medalSprite"] = medalSprite.getPosition();

	rankText.setFont(*_font);
	rankText.setCharacterSize(24 * _scale);
	rankTextOffset = 10.f * _scale;
	startPos["rankText"] = rankText.getPosition();

	highscoreText.setFont(*_font);
	highscoreText.setCharacterSize(16 * _scale);
	highscoreText.setPosition(medalSprite.getPosition().x + rankTextOffset, 1.f * _scale);
	startPos["highscoreText"] = highscoreText.getPosition();
}

void Profile::setProfile(std::string _nickname, std::string _discriminator, int _highscore, bool _isAvatar)
{
	isProfileSet = true;
	nicknameString = _nickname;
	int i = 0;
	while (i < nicknameString.length())
	{
		if (nicknameString[i] >= (char)32 && nicknameString[i] < (char)127)
		{
			i++;
		}
		else
		{
			nicknameString.erase(i);
		}
	}
	while (nicknameString[nicknameString.length() - 1] == (char)32)
	{
		nicknameString.erase(nicknameString.length() - 1);
	}
	nicknameText.setString(nicknameString + " #" + _discriminator);
	highscoreText.setString("highscore: " + std::to_string(_highscore));
	int medal = 0;
	for (int i = 1; i < _highscore; i++)
	{
		if (i % 25 == 0) medal++;
		if (medal < 6)
		{
			medal = 6;
			break;
		}
	}
	medalSprite.setTextureRect(medalTextureRect[medal - 1]);
	rankText.setString(rankNames[medal]);
	rankText.setPosition(medalSprite.getPosition().x + medalSprite.getGlobalBounds().width + rankTextOffset, medalSprite.getGlobalBounds().top);
	startPos["rankText"] = rankText.getPosition();
	highscoreText.move(medalSprite.getGlobalBounds().width, rankText.getGlobalBounds().top + rankText.getGlobalBounds().height);
	startPos["highscoreText"] = highscoreText.getPosition();
	if (_isAvatar)
	{
		avatarTexture.loadFromFile("resources/profile_avatar.png");
		avatarSprite.setTexture(avatarTexture);
		avatarSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		avatarSprite.move(0, -7.f * scale);
		startPos["avatarSprite"] = avatarSprite.getPosition();
	}
	else
	{
		std::cout << "avatar not downloaded\n";
		avatarSprite.setTexture(avatarTexture);
	}
	float avatarScale = avatarScaleHelp / avatarSprite.getLocalBounds().width;
	avatarSprite.setScale(avatarScale, avatarScale);
}

void Profile::move(float _amount)
{
	backgroundTemp.move(0, _amount);

	backgroundSprite.move(0, _amount);
	medalSprite.move(0, _amount);
	rankText.move(0, _amount);
	highscoreText.move(0, _amount);
	avatarBackground.move(0, _amount);
	avatarSprite.move(0, _amount);
	nicknameText.move(0, _amount);
}

void Profile::reset()
{
	backgroundTemp.setPosition(startPos["backgroundSprite"]);

	backgroundSprite.setPosition(startPos["backgroundSprite"]);
	medalSprite.setPosition(startPos["medalSprite"]);
	rankText.setPosition(startPos["rankText"]);
	highscoreText.setPosition(startPos["highscoreText"]);
	avatarBackground.setPosition(startPos["avatarBackground"]);
	avatarSprite.setPosition(startPos["avatarSprite"]);
	nicknameText.setPosition(startPos["nicknameText"]);
}

float Profile::getDistanceToTravel()
{
	float distance = startPos["avatarSprite"].y - avatarSprite.getPosition().y;
	return distance;
}

void Profile::setHover(sf::Vector2f _mouse)
{
	isHover = backgroundRect.contains(_mouse);
}

bool Profile::getHover()
{
	return isHover;
}

void Profile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isProfileSet) return;
	target.draw(backgroundTemp);
	target.draw(backgroundSprite);
	target.draw(medalSprite);
	target.draw(rankText);
	target.draw(highscoreText);
	//target.draw(avatarBackground);
	target.draw(avatarSprite);
	target.draw(nicknameText);
}