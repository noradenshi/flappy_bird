#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "Button.h"
#include "Profile.h"
#include "Leaderboard.h"

class UI : public sf::Drawable
{
private:
	Profile profile;
	Buttons buttons;
	Leaderboard leaderboard;
	sf::Text title;
	sf::Text info;
	sf::Text scoreText;
	sf::Text highscoreText;
	sf::Text newBest;
	sf::Texture scoreBoxTexture;
	sf::Sprite scoreBox;
	sf::RectangleShape scoreBoxShadow;
	sf::Texture medalTexture;
	sf::IntRect medalTextureRect[6];
	sf::Sprite medal;
	sf::Texture musicMuteTexture;
	sf::IntRect musicMuteTextureRect[2];
	sf::Sprite musicMute;
	sf::FloatRect musicMuteRect;
	sf::Text fpsText;
	sf::SoundBuffer muteBuffer[2];
	sf::Sound sound;
	sf::SoundBuffer pointBuffer;

	bool showLeaderboard = false;
	bool fpsShow = false;
	int fpsCounter;
	float fpsTimer = 0.f;
	float speed = 160.f;
	sf::Vector2i w_size;
	bool isMenu = true;
	bool isTitleVisible = true;
	bool isDead = false;
	bool doReset = false;
	bool showResult = false;
	bool isNewBest = false;
	float pointsInterval = 0.f;
	float timeToWait = 0.f;
	int points = 0;
	int pointsAnim = 0;
	int highscore = 0;
	int currentMedal = -1;
	bool medalAnimate = false;
	float medalScale;
	sf::Vector2f medalOffset;
	sf::Vector2f musicMuteStartPos;
	int medalAnimationStage = 0; //0- start; 1- wait; 2- end 
	float medalScaleSpeed = 30;
	float medalRotationSpeed = 120;
	int medalDirection = 0;
	bool scoreCounting = false;
	bool isMute = false;
	bool muteHover = false;

	std::fstream highscoreFile;
	std::fstream optionsFile;

public:
	UI(sf::Font*, sf::Vector2i, float);
	void setProfile(std::string, std::string, bool);
	void updateMouse(sf::Vector2f _mouse) { buttons.checkCollisions(_mouse); profile.setHover(_mouse); };
	void mouseClick();
	void update(float);
	void showFPS();
	void createLeaderboard(std::vector<std::string> nicknames, std::vector<std::string> discriminators) { leaderboard.createList(nicknames, discriminators); }
	void setMenu(bool);
	void setPoints(int);
	bool getMenu();
	void setDeath(bool);
	bool getDeath();
	void reset();
	bool isReset() { return !doReset; }
	bool isScoreCounted() { return !scoreCounting; }
	int getHighscore() { return highscore; }
	sf::FloatRect getMuteRect() { return musicMuteRect; }
	void setMuteHover(bool _val) { muteHover = _val; };
	bool getHover();
	bool getMuteHover() { return muteHover; }
	void setMute();
	void setMute(bool);
	bool getMute() { return isMute; }
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};