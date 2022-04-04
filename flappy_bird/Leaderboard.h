#pragma once
#include <SFML/Graphics.hpp>

class LeaderboardProfile : public sf::Drawable
{
private:
	sf::RectangleShape backgroundTemp;
	sf::Text position;
	sf::Sprite avatar;
	sf::Text nickname;
	sf::Text highscore;
	sf::Sprite rank;

public:
	LeaderboardProfile() = default;
	LeaderboardProfile(sf::Font*, float, sf::Vector2f, int, std::string);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

class Leaderboard : public sf::Drawable
{
private:
	sf::RectangleShape backgroundTemp;
	std::vector<LeaderboardProfile> players;
	sf::Vector2f startPos;
	sf::Font font;
	float scale;

public:
	Leaderboard() = default;
	Leaderboard(sf::Font*, sf::Vector2f, float);
	void createList(std::vector<std::string>, std::vector<std::string>);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};

