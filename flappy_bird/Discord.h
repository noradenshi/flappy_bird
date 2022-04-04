#pragma once
#include "discord/discord.h"
#include "UI.h"
#include <chrono>
#include <string>

class Discord
{
private:
	discord::Core* core{};
	discord::User user{};
	discord::ImageDimensions dims{};
	discord::Activity activity{};
	//discord::RelationshipManager &relationshipManager;
	int highscore = 0;
	int rank = 0;
	std::string rankNames[7] = { "rookie", "bronze", "silver", "gold", "platinum", "master", "grandmaster"};
	bool isActive = false;
	bool isAvatar = false;

	void OnCurrentUserUpdate();
	void OnRelationshipRefresh();
	UI *ui;

public:
	
	Discord(UI*);

	void updateHighscore(int);
	void update();
	~Discord();
};