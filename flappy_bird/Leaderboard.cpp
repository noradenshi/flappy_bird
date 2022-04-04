#include "Leaderboard.h"
#include <iostream>

LeaderboardProfile::LeaderboardProfile(sf::Font* _font, float _scale, sf::Vector2f _pos, int _position, std::string _nickname)
{
	position.setFont(*_font);
	position.setCharacterSize(12.f * _scale);
	position.setFillColor(sf::Color(255, 255, 255));
	position.setPosition(_pos);
	position.setString(std::to_string(_position));

	nickname.setFont(*_font);
	nickname.setCharacterSize(10.f * _scale);
	nickname.setFillColor(sf::Color(255, 255, 255));
	nickname.setPosition(_pos.x + 50.f, _pos.y);
	nickname.setString(_nickname);
}

void LeaderboardProfile::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(backgroundTemp);
	target.draw(position);
	target.draw(avatar);
	target.draw(nickname);
	target.draw(highscore);
	target.draw(rank);
}


Leaderboard::Leaderboard(sf::Font* _font, sf::Vector2f _pos, float _scale)
{
	font = *_font;
	startPos = _pos;
	scale = _scale;

	backgroundTemp.setSize(sf::Vector2f(300.f * _scale, 600.f * _scale));
	backgroundTemp.setPosition(_pos);
	backgroundTemp.setFillColor(sf::Color((200, 168, 171, 100)));
}

void Leaderboard::createList(std::vector<std::string> nicknames, std::vector<std::string> discriminators)
{
	for (auto& a : nicknames)
	{
		std::string nicknameString = nicknames[players.size()];
		std::cout << nicknameString << " " << players.size() << std::endl;
		int i = 0;
		while (i < nicknameString.length())
		{
			if (nicknameString[i] >= (char)32 && nicknameString[i] < (char)127)
			{
				i++;
			}
			else
			{
				if (nicknameString.length() > 1)
					nicknameString.erase(i);
				else
					nicknameString = " ";
			}
		}
		while (nicknameString.length() > 1 && nicknameString[nicknameString.length() - 1] == (char)32)
		{
			nicknameString.erase(nicknameString.length() - 1);
		}
		nicknameString += "     #" + discriminators[players.size()];
		players.emplace_back(&font, scale, sf::Vector2f(startPos.x + 10.f * scale, startPos.y + 15.f * players.size()), players.size() + 1, nicknameString);
	}
}

void Leaderboard::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(backgroundTemp);
	for (auto& a : players)
		target.draw(a);
}