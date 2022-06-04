#include "Discord.h"
#include <iostream>

void Discord::OnCurrentUserUpdate()
{
	core->UserManager().GetCurrentUser(&user);

	discord::ImageHandle handle{};
	handle.SetId(user.GetId());
	handle.SetType(discord::ImageType::User);
	handle.SetSize(64);
	isAvatar = false;
	core->ImageManager().Fetch(handle, false, [&](discord::Result res, discord::ImageHandle handle) {
		if (res == discord::Result::Ok)
		{
			isAvatar = true;
			core->ImageManager().GetDimensions(handle, &dims);
			std::cout << "[Discord] Fetched " << dims.GetWidth() << "x" << dims.GetHeight() << " avatar!\n";
			//download image
		}
		else
			std::cout << "[Discord] Failed to fetch avatar! Error code:  " << static_cast<int>(res) << std::endl;
		});

	ui->setProfile(user.GetUsername(), user.GetDiscriminator(), isAvatar);
}

void Discord::OnRelationshipRefresh()
{
	auto relationshipManager = &core->RelationshipManager();
	relationshipManager->Filter([](discord::Relationship const& relation) {
		return relation.GetType() == discord::RelationshipType::Friend;
	});

	int num;
	auto res = relationshipManager->Count(&num);
	std::cout << static_cast<int>(res) << " Relationship updated: " << num << std::endl;

	discord::Relationship relation{};
	std::vector<std::string> nicknames, discriminators;
	for (int i=0; i<num; i++)
	{
		relationshipManager->GetAt(i, &relation);
		nicknames.emplace_back(relation.GetUser().GetUsername());
		discriminators.emplace_back(relation.GetUser().GetDiscriminator());
		//auto res = relationshipManager->GetAt(i, &relation);
		//std::cout << static_cast<int>(res) << " ";
		//std::cout << relation.GetUser().GetId() << ": " << relation.GetUser().GetUsername() << " #" << relation.GetUser().GetDiscriminator() << std::endl;
	}
	ui->createLeaderboard(nicknames, discriminators);
}

Discord::Discord(UI *_ui)
{
	ui = _ui;
	discord::Result result = discord::Core::Create(860237215601786920, DiscordCreateFlags_NoRequireDiscord, &core);
	if (result != discord::Result::Ok)
	{
		std::cout << "discord not running!\n";
		return;
	}

	core->UserManager().OnCurrentUserUpdate.Connect([&]() { OnCurrentUserUpdate(); });
	core->RelationshipManager().OnRefresh.Connect([&]() { OnRelationshipRefresh(); });

	isActive = true;
	activity.SetType(discord::ActivityType::Playing);
	activity.SetDetails("by .noradenshi");
	activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	activity.GetAssets().SetLargeImage("bird");

	updateHighscore(ui->getHighscore());
}

void Discord::updateHighscore(int _highscore)
{
	if (_highscore < highscore || !isActive) return;
	highscore = _highscore;
	rank = 0;
	for (int i = 1; i <= highscore; i++)
	{
		if (i > 1 && i % 25 == 0 && i <= 150)
		{
			rank++;
		}
	}
	activity.SetState(("highscore: " + std::to_string(highscore)).c_str());
	activity.GetAssets().SetSmallImage(rankNames[rank].c_str());
	activity.GetAssets().SetSmallText(rankNames[rank].c_str());
	core->ActivityManager().UpdateActivity(activity, nullptr);
}

void Discord::update()
{
	if (!isActive) return;
	core->RunCallbacks();
	//std::cout << "username" << user.GetUsername() << std::endl;
}

Discord::~Discord()
{
	if (!isActive) return;
	//core->ActivityManager().ClearActivity(nullptr);
	core->~Core();
}