#pragma once
#include <SFML/Graphics.hpp>

class Profile : public sf::Drawable
{
private:
	std::string nicknameString;
	sf::Text nicknameText;
	sf::Texture avatarTexture;
	sf::Sprite avatarSprite;
	sf::CircleShape avatarBackground;
	sf::Sprite medalSprite;
	sf::IntRect medalTextureRect[6];
	std::string rankNames[7] = { "rookie", "bronze", "silver", "gold", "platinum", "master", "grandmaster" };
	sf::Text rankText;
	sf::Text highscoreText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::RectangleShape backgroundTemp;
	std::map<std::string, sf::Vector2f> startPos;
	float rankTextOffset = 0.f;
	float avatarScaleHelp = 1.f;
	bool isProfileSet = false;
	float scale;
	
	sf::FloatRect backgroundRect;
	bool isHover = false;

public:
	Profile();
	Profile(sf::Font*, sf::Texture*, sf::IntRect[], float);
	void setProfile(std::string, std::string, int, bool);
	void move(float);
	void reset();
	float getDistanceToTravel();
	void setHover(sf::Vector2f);
	bool getHover();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};