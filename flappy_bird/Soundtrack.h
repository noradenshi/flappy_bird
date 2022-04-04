#include <SFML/Audio.hpp>

class Soundtrack
{
private:
	sf::Music soundtrack;
	bool changeMusic = false;
	int nextSongID = 1;
	bool isMute;

public:
	Soundtrack();
	void play(int);
	void setMute(bool);
	void swap();
	void update();
	void reset();	
};