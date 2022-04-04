#include <SFML/Graphics.hpp>
#include "Bird.h" 
#include "Score.h"
#include "Border.h"
#include "Pipe.h"
#include "Background.h"
#include "UI.h"
#include "Soundtrack.h"
#include "Camera.h"
#include "discord/discord.h"
#include "Discord.h"
#include <iostream>
#include <fstream>

void SaveAndClose(sf::RenderWindow& window, Discord& discord, bool _isMute)
{
	std::fstream optionsFile("resources/options", std::ios::out);
	optionsFile << "mute: " + std::to_string(_isMute);
	optionsFile.close();
	discord.~Discord();
	window.close();
}

int main()
{
	//sf::Vector2i w_size(1280, 720);
	sf::Vector2i w_size(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	float scale = w_size.y / 768.f;
	if (w_size.y < 768.f)
	{
		float diff = 768.f - w_size.y;
		w_size.y = 768.f;
		w_size.x -= diff;
		scale = 1.f;
	}
	sf::RenderWindow window(sf::VideoMode(w_size.x, w_size.y), "flappus da birdus", sf::Style::Fullscreen  );
	sf::Mouse::setPosition(w_size);
	sf::Image icon;
	icon.loadFromFile("resources/bird_icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	srand(time(0));
	sf::Clock pipeSpawner;
	sf::Time nextPipe = sf::seconds(2.f);
	float nextPipeHeight = rand() % 400 * scale + 151.f * scale;
	float prevPipeHeight = 0.f;
	sf::Clock timer;
	float deltaTime;
	//fonts
	sf::Font font; font.loadFromFile("resources/LemonMilk.otf");
	//textures
	sf::Texture bird_texture; bird_texture.loadFromFile("resources/bird.png");
	sf::Texture pipe_texture; pipe_texture.loadFromFile("resources/pipe.png");
	sf::Texture iceCream_texture; iceCream_texture.loadFromFile("resources/ice-cream.png");
	sf::Texture background_texture; background_texture.loadFromFile("resources/background.png");

	Background background(&background_texture, (sf::Vector2f)w_size, scale);
	Border border(sf::Vector2f(w_size.x, 40.f * scale), sf::Vector2f(w_size.x / 2, w_size.y));
	Bird bird(&bird_texture, sf::Vector2f(w_size.x/2, w_size.y/2), border.getRect(), scale);
	Score score(&font, sf::Vector2f(w_size.x / 2, 50.f * scale), scale);
	Pipes pipes(sf::Vector2f(w_size.x + 160.f, nextPipeHeight), &pipe_texture, &iceCream_texture, scale);
	UI ui(&font, w_size, scale);
	Soundtrack soundtrack;
	soundtrack.setMute(ui.getMute());
	Camera camera(w_size, scale);
	Discord discord(&ui);

	sf::View uiView;
	uiView.setCenter(w_size.x / 2, w_size.y / 2);
	uiView.setSize(w_size.x, w_size.y);

	float gameSpeed = 1.15f; 
	float gameAcceleration = .15; //.0004f;
	int scoreLastSpedUp = 0;

	while (window.isOpen())
	{
		discord.update();
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { SaveAndClose(window, discord, ui.getMute()); }
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) { SaveAndClose(window, discord, ui.getMute()); }
				if (event.key.code == sf::Keyboard::F10) ui.showFPS();
				if (event.key.code == sf::Keyboard::M && ui.getMenu()) { ui.setMute(); soundtrack.setMute(ui.getMute()); }
				if (event.key.code == sf::Keyboard::Up && !bird.isDead()) { bird.flap(); if (ui.getMenu()) { ui.setMenu(false); pipes.setMove(true); } }
				if (event.key.code == sf::Keyboard::Enter && bird.isDead() && ui.isScoreCounted()) { bird.reset(); pipes.reset(); ui.reset(); score.setScore(0); gameSpeed = 1.f;
					soundtrack.reset(); camera.reset(window); nextPipe = sf::seconds(2.f); }
			}
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mouse(sf::Mouse::getPosition(window));
				ui.updateMouse(mouse);
				if (ui.getMuteRect().contains(mouse)) 
					ui.setMuteHover(true);
				else if (ui.getMuteHover()) 
					ui.setMuteHover(false);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (ui.getMuteHover())
				{
					ui.setMute();
					soundtrack.setMute(ui.getMute());
				}
				if (ui.getHover())
				{
					ui.mouseClick();
					break;
				}

				if (bird.isDead() && ui.isScoreCounted())
				{
					bird.reset(); pipes.reset(); ui.reset(); score.setScore(0); gameSpeed = 1.f;
					soundtrack.reset(); camera.reset(window); nextPipe = sf::seconds(2.f);
				}
				else
				{
					bird.flap();
					if (ui.getMenu())
					{
						ui.setMenu(false);
						pipes.setMove(true);
					}
				}
			}
		}

		camera.update(window, deltaTime);
		ui.update(deltaTime);
		pipes.update(deltaTime, gameSpeed);
		soundtrack.update();

		if (bird.isDead() && !ui.getDeath())
		{
			discord.updateHighscore(score.getScore());
			ui.setPoints(score.getScore());
			ui.setDeath(true);
			camera.fall();
			pipes.setMove(false);
		}
		if (!ui.getMenu() && !bird.isDead())
		{
			if (score.getScore() > 1  && score.getScore() <= 125 && score.getScore() % 10 == 0 && scoreLastSpedUp != score.getScore())
			{ 
				gameSpeed += gameAcceleration; 
				scoreLastSpedUp = score.getScore();
				//std::cout << gameSpeed << std::endl;
			}
			bird.update(deltaTime);
			if (!bird.isHit())
			{
				background.update(deltaTime, gameSpeed);
				for (auto& a : pipes.buffor)
				{
					if (bird.checkCollisions(a.getRect()))
					{
						score.addScore(a.getPoints(score.getScore()));
						if (score.getScore() == 10) { soundtrack.play(1); }
						else if (score.getScore() == 50) { soundtrack.play(3); }
						else if (score.getScore() > 60 && score.getScore() % 25 == 0) 
						{ 
							soundtrack.swap(); 
						}
					}
				}
			}
			else
			{
				camera.shake();
				pipes.setMove(false);
			}

			if (pipeSpawner.getElapsedTime().asSeconds() >= nextPipe.asSeconds())
			{
				pipes.create(nextPipeHeight);
				prevPipeHeight = nextPipeHeight;
				nextPipeHeight = (rand() % 400 * scale) + 151.f * scale;
				int diff = prevPipeHeight - nextPipeHeight;
				if (diff < 0) diff = -diff; 
				if (diff < 2 * scale) diff = 2.f * scale;
				nextPipe = sf::seconds((std::log10(diff / scale) + .6f) / gameSpeed);
				pipeSpawner.restart();
				//std::cout << "diff: " << diff << " nextPipe: " << std::to_string(nextPipe.asSeconds()) << std::endl;
			}
		}

		window.clear();
		window.draw(background);
		for (auto& a : pipes.buffor) window.draw(a);
		window.draw(border);
		window.draw(bird);
		if (!ui.getMenu() && !bird.isDead()) window.draw(score);
		window.setView(uiView);
		window.draw(ui);
		window.display();
	}
}