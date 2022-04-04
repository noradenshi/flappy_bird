#include "UI.h"
#include <iostream>

UI::UI(sf::Font* _font, sf::Vector2i _w_size, float _scale)
{
	buttons = Buttons(sf::Vector2f(3.f * _scale, _w_size.y / 2 - 150.f * _scale), _font, _scale, _w_size);
	leaderboard = Leaderboard(_font, sf::Vector2f(100.f * _scale, 100.f * _scale), _scale);
	sf::FloatRect temp;
	w_size = _w_size;

	speed *= _scale;

	title.setCharacterSize(64 * _scale);
	title.setFont(*_font);
	title.setFillColor(sf::Color::White);
	title.setString("Flappus\n   da Birdus");
	title.setPosition(_w_size.x / 2, _w_size.y / 2);
	temp = title.getLocalBounds();
	title.setOrigin(temp.width / 2, temp.height + 150.f * _scale);

	info.setCharacterSize(28 * _scale);
	info.setFont(*_font);
	info.setFillColor(sf::Color::White);
	info.setString("Press UP to flap()");
	info.setPosition(_w_size.x / 2, _w_size.y / 2);
	temp = info.getLocalBounds();
	info.setOrigin(temp.width / 2, temp.height - 180.f * _scale);

	musicMuteTexture.loadFromFile("resources/music.png");
	musicMuteTextureRect[0] = sf::IntRect(0, 0, 16, 16);
	musicMuteTextureRect[1] = sf::IntRect(16, 0, 16, 16);
	musicMute.setTexture(musicMuteTexture);
	musicMute.setTextureRect(musicMuteTextureRect[0]);
	temp = musicMute.getLocalBounds();
	musicMute.setOrigin(temp.width / 2, temp.height / 2);
	musicMute.setScale(4 * _scale, 4 * _scale);
	musicMute.setPosition(sf::Vector2f(w_size.x - (musicMute.getGlobalBounds().width/2 + 10.f * _scale), musicMute.getGlobalBounds().height/2 + 12.f * _scale));
	musicMuteStartPos = musicMute.getPosition();
	musicMuteRect = musicMute.getGlobalBounds();
	muteBuffer[0].loadFromFile("resources/sounds/unmute.wav");
	muteBuffer[1].loadFromFile("resources/sounds/mute.wav");
	pointBuffer.loadFromFile("resources/sounds/point.wav");

	optionsFile.open("resources/options", std::ios::in);
	if (optionsFile.good())
	{
		std::string tempS;
		std::getline(optionsFile, tempS);
		if (tempS.size() > 1)
		{
			size_t pos;
			if (pos = tempS.find_last_of("mute: "))
			{
				tempS.erase(0, pos);
				isMute = std::atoi(tempS.c_str());
				musicMute.setTextureRect(musicMuteTextureRect[isMute]);
			}
		}
	}

	highscoreFile.open(("resources/score"), std::ios::in);
	if (highscoreFile.good())
	{
		std::string tempS;
		std::getline(highscoreFile, tempS);
		if (tempS.size() > 8)
		{
			int key = (tempS[0] - 48) * 10 + tempS[1] - 48;
			int lenght = tempS[2] - 48;
			int mod10 = tempS[3] - 48;
			int mod50 = ((tempS[4] - 48) * 100 + (tempS[5] - 48) * 10 + tempS[6] - 48) / 2;
			std::string nums;
			for (int i = 0; i < lenght; i++)
			{
				nums += tempS[i + 7];
			}
			for (int i = 0; i < nums.size(); i++)
			{
				nums[i] = nums[i] ^ key;
			}
			int num = std::atoi(nums.c_str());

			if (num % 10 == mod10 && num % 50 == mod50)
			{
				highscore = num;
				//std::cout << "highscore read: " << highscore;
			}
			else highscore = 0;
		}
		else highscore = 0;
	}
	else highscore = 0;
	highscoreFile.close();

	scoreBoxTexture.loadFromFile("resources/scoreBox.png");
	scoreBox.setTexture(scoreBoxTexture);
	float scale = 300.f / scoreBox.getLocalBounds().height;
	scoreBox.setScale(scale * _scale, scale * _scale);
	scoreBox.setPosition(w_size.x / 2, w_size.y + scoreBox.getLocalBounds().height);
	scoreBox.setOrigin(scoreBox.getLocalBounds().width / 2, scoreBox.getLocalBounds().height / 2);

	scoreBoxShadow.setFillColor(sf::Color(0, 0, 0, 100));
	scoreBoxShadow.setSize(sf::Vector2f(w_size));
	scoreBoxShadow.setOrigin(scoreBoxShadow.getSize().x / 2, scoreBoxShadow.getSize().y / 2);
	scoreBoxShadow.setPosition(scoreBox.getPosition());

	scoreText.setCharacterSize(48 * _scale);
	scoreText.setFont(*_font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("0");
	scoreText.setPosition(scoreBox.getPosition().x - temp.width / 2, scoreBox.getPosition().y);
	temp = scoreText.getLocalBounds();
	scoreText.setOrigin(-120.f * _scale, (temp.height / 2) + (50.f * _scale));

	highscoreText.setCharacterSize(48 * _scale);
	highscoreText.setFont(*_font);
	highscoreText.setFillColor(sf::Color::White);
	highscoreText.setString(std::to_string(highscore));
	temp = highscoreText.getLocalBounds();
	highscoreText.setPosition(scoreBox.getPosition().x - temp.width / 2, scoreBox.getPosition().y);
	highscoreText.setOrigin(-120.f * _scale, (temp.height / 2) - (70.f * _scale));
	
	medalTextureRect[0] = sf::IntRect(0, 0, 22, 22);
	medalTextureRect[1] = sf::IntRect(23, 0, 22, 22);
	medalTextureRect[2] = sf::IntRect(0, 23, 22, 22);
	medalTextureRect[3] = sf::IntRect(23, 23, 22, 22);
	medalTextureRect[4] = sf::IntRect(0, 46, 22, 22);
	medalTextureRect[5] = sf::IntRect(23, 46, 22, 22);
	medalTexture.loadFromFile("resources/medals.png");
	medal.setTexture(medalTexture);
	medal.setTextureRect(medalTextureRect[0]);
	medalScale = (336.f * scale / medal.getLocalBounds().width) * _scale;
	medal.setScale(medalScale, medalScale);
	medalOffset = { 162.5f * _scale, 27.5f * _scale };
	medal.setPosition(scoreBox.getPosition().x - medalOffset.x, scoreBox.getPosition().y + medalOffset.y);
	medal.setOrigin(medal.getLocalBounds().width / 2, medal.getLocalBounds().height / 2);

	profile = Profile(_font, &medalTexture, medalTextureRect, _scale);

	newBest.setCharacterSize(32 * _scale);
	newBest.setFont(*_font);
	newBest.setFillColor(sf::Color::Red);
	newBest.setString("new");
	newBest.setRotation(-15.f);
	newBest.setPosition(w_size.x / 2, w_size.y / 2);
	temp = newBest.getLocalBounds();
	newBest.setOrigin(temp.width / 2, temp.height / 2);

	fpsText.setCharacterSize(28 * _scale);
	fpsText.setFont(*_font);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(sf::Vector2f(10.f * _scale, 10.f * _scale));
}

void UI::setProfile(std::string _nickname, std::string _discriminator, bool _isAvatar)
{
	profile.setProfile(_nickname, _discriminator, highscore, _isAvatar);
	buttons.setActive(true);
}

void UI::showFPS()
{
	fpsShow = !fpsShow;
	fpsCounter = 0; 
	fpsTimer = 0.f;
}

void UI::update(float _deltaTime)
{
	if (muteHover)
	{
		musicMute.setColor(sf::Color(235, 235, 235, 255));
	}
	else
	{
		musicMute.setColor(sf::Color(255, 255, 255, 255));
	}

	if (fpsShow) 
	{
		fpsCounter++;
		fpsTimer += _deltaTime;
		if (fpsTimer >= 1.f)
		{
			fpsText.setString("fps: " + std::to_string(fpsCounter));
			fpsTimer = 0.f;
			fpsCounter = 0;
		}
	}

	if (isDead && !showResult)
	{
		if (medalAnimate)
		{ 
			if (medalAnimationStage == 0)
			{
				medal.setScale(medal.getScale().x + medalScaleSpeed * _deltaTime, medal.getScale().y + medalScaleSpeed * _deltaTime);
				medal.rotate(medalDirection * medalRotationSpeed * _deltaTime);
				
				if (medal.getScale().x >= medalScale + 3.f)
				{
					medalAnimationStage = 1;
				}
			}
			else if (medalAnimationStage == 2)
			{
				medal.setScale(medal.getScale().x - medalScaleSpeed * 4 * _deltaTime, medal.getScale().y - medalScaleSpeed * 4 * _deltaTime);
				medal.rotate(medalDirection * medalRotationSpeed * _deltaTime);

				if (medal.getScale().x <= medalScale)
				{
					medal.setRotation(0.f);
					medal.setScale(medalScale, medalScale);
					medal.setPosition(scoreBox.getPosition().x - medalOffset.x, scoreBox.getPosition().y + medalOffset.y);
					medalAnimationStage = 0;
					medalAnimate = false;
				}
			}
		}
		pointsInterval += _deltaTime;
		if (pointsInterval >= timeToWait)
		{
			if (medalAnimationStage == 1) medalAnimationStage = 2;
			pointsInterval = 0.f;			

			if (pointsAnim < points)
			{
				if (pointsAnim > 0) sound.play();
				scoreText.setString(std::to_string(pointsAnim));
				scoreText.setPosition(scoreBox.getPosition().x - scoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
				pointsAnim++;
				if (pointsAnim < points) timeToWait = ((float)pointsAnim / (float)points) * ((float)pointsAnim / (float)points) / 20.f;
				else timeToWait = .4f;
				if (currentMedal < 5 && pointsAnim % 25 == 0)
				{
					currentMedal++;
					medal.setTextureRect(medalTextureRect[currentMedal]);
					medalAnimate = true;
					medalDirection = rand() % 2;
					if (medalDirection == 0) 
						medalDirection = -1;
				}
			}
			else
			{                
				if(scoreCounting) sound.play();
				scoreText.setString(std::to_string(pointsAnim));
				scoreText.setPosition(scoreBox.getPosition().x - scoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
				scoreCounting = false;
				if (points > highscore)
				{
					highscore = points;
					highscoreText.setString(std::to_string(highscore));
					highscoreText.setPosition(scoreBox.getPosition().x - highscoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
					isNewBest = true;
					highscoreFile.open(("resources/score"), std::ios::out);
					int key = rand() % 90 + 10;
					highscoreFile << std::to_string(key);
					highscoreFile << std::to_string(points).size();
					highscoreFile << std::to_string(points % 10);
					int mod50 = points % 50 * 2;
					int zeros = 3 - std::to_string(mod50).size();
					for (int i = 0; i < zeros; i++)
					{
						highscoreFile << "0";
					}
					highscoreFile << std::to_string(mod50);
					std::string num = std::to_string(points);
					for (int i = 0; i < num.size(); i++)
					{
						num[i] = num[i] ^ key;
					}
					highscoreFile << num;
					highscoreFile << std::to_string(rand() % 90 + 10);
					highscoreFile.close();
				}
			}
		}
	}

	if (showResult)
	{
		float temp = _deltaTime * -speed * 15.f;
		scoreBox.move(0, temp);
		profile.move(_deltaTime * 15.f * profile.getDistanceToTravel());
		if (scoreBox.getPosition().y <= w_size.y / 2)
		{
			profile.reset();
			scoreBox.setPosition(w_size.x / 2, w_size.y / 2);
			showResult = false;
		}
		scoreBoxShadow.setPosition(scoreBox.getPosition());
		medal.setPosition(scoreBox.getPosition().x - medalOffset.x, scoreBox.getPosition().y + medalOffset.y);
		scoreText.setPosition(scoreBox.getPosition().x - scoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
		highscoreText.setPosition(scoreBox.getPosition().x - highscoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
	}

	if (isTitleVisible && !isDead && !isMenu)
	{
		float temp = _deltaTime * -speed;
		title.move(temp, 0);
		info.move(temp, 0);
		profile.move(temp);
		buttons.move(temp);
		musicMute.move(0, temp);
		musicMuteRect = musicMute.getGlobalBounds();
		if (title.getGlobalBounds().left + title.getGlobalBounds().width < -10) isTitleVisible = false;
	}

	if (doReset)
	{
		float temp = _deltaTime * speed * 10.f;
		buttons.move(temp);
		title.move(temp, 0);
		info.move(temp, 0);
		musicMute.move(0, temp);
		scoreBox.move(0, temp * 2.f);
		if (title.getPosition().x >= w_size.x/2)
		{
			buttons.reset();
			title.setPosition(w_size.x / 2, w_size.y / 2);
			info.setPosition(w_size.x / 2, w_size.y / 2);
			musicMute.setPosition(musicMuteStartPos);
			musicMuteRect = musicMute.getGlobalBounds();
			scoreBox.setPosition(w_size.x / 2, w_size.y + scoreBox.getLocalBounds().height);
			doReset = false;
			isDead = false;
			points = 0;
			pointsAnim = 0;
			timeToWait = 0.f;
			scoreText.setString("0");
			medalAnimationStage = 0;
			medalAnimate = false;
			currentMedal = -1;
			medal.setTextureRect(medalTextureRect[currentMedal]);
			medal.setRotation(0.f);
			medal.setScale(medalScale, medalScale);
			medal.setPosition(scoreBox.getPosition().x - medalOffset.x, scoreBox.getPosition().y + medalOffset.y);
		}
		scoreBoxShadow.setPosition(scoreBox.getPosition());
		scoreText.setPosition(scoreBox.getPosition().x - scoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
		highscoreText.setPosition(scoreBox.getPosition().x - highscoreText.getLocalBounds().width / 2, scoreBox.getPosition().y);
		medal.setPosition(scoreBox.getPosition().x - medalOffset.x, scoreBox.getPosition().y + medalOffset.y);
	}
}

void UI::setMenu(bool _val)
{
	isMenu = _val;
}
bool UI::getMenu()
{
	return isMenu;
}

void UI::setPoints(int _val)
{
	points = _val;
}

void UI::setDeath(bool _value)
{
	isDead = _value;
	if (isDead)
	{
		sound.setBuffer(pointBuffer);
		showResult = true;
		scoreCounting = true;
	}
}
bool UI::getDeath()
{
	return isDead;
}

void UI::reset()
{
	doReset = true;
	isMenu = true;
	isTitleVisible = true;
	showResult = false;
	isNewBest = false;
}

void UI::setMute()
{
	isMute = !isMute;
	sound.setBuffer(muteBuffer[isMute]);
	sound.play();
	musicMute.setTextureRect(musicMuteTextureRect[isMute]);
}

void UI::setMute(bool _val)
{
	isMute = _val;
	musicMute.setTextureRect(musicMuteTextureRect[_val]);
}

void UI::mouseClick()
{
	if (buttons.getHover())
	{
		std::string temp = buttons.mouseClick();
		showLeaderboard = (temp == "leaderboards" && !showLeaderboard);
	}
	else
	{
		showLeaderboard = false;
	}
}

bool UI::getHover()
{
	return buttons.getHover() | muteHover | profile.getHover();
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isTitleVisible) 
	{
		target.draw(title);
		target.draw(info);
		target.draw(musicMute);
		target.draw(buttons);
	}
	if (isDead)
	{
		target.draw(scoreBoxShadow);
		target.draw(scoreBox);
		target.draw(scoreText);
		target.draw(highscoreText);
		if (currentMedal > -1) target.draw(medal);
		if (isNewBest) target.draw(newBest);
	}
	if (showLeaderboard)
	{
		target.draw(leaderboard);
	}
	if (fpsShow)
	{
		target.draw(fpsText);
	}
	target.draw(profile);
}