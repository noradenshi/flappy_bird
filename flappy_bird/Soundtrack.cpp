#include "Soundtrack.h"

Soundtrack::Soundtrack()
{
	soundtrack.setVolume(100);
	//soundtrack.setVolume(40);
	soundtrack.openFromFile("resources/music/lofi1.wav");
	soundtrack.setLoop(true);
	soundtrack.play();
}

void Soundtrack::play(int _id)
{
	changeMusic = true;
	nextSongID = _id + 1;
	soundtrack.setLoop(false);
}

void Soundtrack::setMute(bool _val)
{
	isMute = _val;
	if (!_val)
	{
		nextSongID = 1;
		soundtrack.openFromFile("resources/music/lofi1.wav");
		soundtrack.setLoop(true);
		soundtrack.play();
	}
	else
	{
		soundtrack.stop();
	}
}

void Soundtrack::swap()
{
	changeMusic = true;
	soundtrack.setLoop(false);
	if (nextSongID == 4) nextSongID = 5;
	else				 nextSongID = 4;
}

void Soundtrack::update()
{
	if (soundtrack.getStatus() == sf::SoundStream::Playing || !changeMusic || isMute) return;
	soundtrack.openFromFile("resources/music/lofi" + std::to_string(nextSongID) + ".wav");
	soundtrack.play();
	soundtrack.setLoop(true);
	changeMusic = false;
	if (nextSongID == 2)
	{
		changeMusic = true;
		soundtrack.setLoop(false);
		nextSongID = 3;
	}
}

void Soundtrack::reset()
{
	changeMusic = true;
	soundtrack.setLoop(false);
	nextSongID = 1;
}

