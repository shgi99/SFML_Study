#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "CloudGo.h"
#include "BeeGo.h"
#include "TreeGo.h"
#include "PlayerGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "UITimeBar.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	for (int i = 0; i < 5; i++)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->SetRangeScale({ 1.f, 2.f });
		cloud->SetBounds({ -300.f, 2220.f });
		cloud->SetPosition({ 0.f, Utils::RandomRange(100.f, 540.f)});

		BeeGo* bee = AddGo(new BeeGo("graphics/bee.png"));
		bee->SetBounds({ -300.f, 2220.f });
		bee->SetPosition({ 0.f, Utils::RandomRange(540.f, 800.f) });
	}

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/rip.png");

	tree = AddGo(new TreeGo("Tree"));
	player = AddGo(new PlayerGo("Player"));
	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf","Center Message"));
	uiScore = AddGo(new UIScore("fonts/KOMIKAP_.ttf", "UI Score"));
	uiTimebar = AddGo(new UITimeBar("UI Timebar"));

	Scene::Init();

	tree->SetPosition({ 1920 / 2, 1080.f - 300.f });

	player->SetPosition({ 1920 / 2, 1080.f - 300.f });

	centerMsg->SetTextSize(100);
	centerMsg->SetTextColor(sf::Color::White);
	centerMsg->SetPosition({ 1920 / 2.f, 1080.f / 2.f });

	uiScore->SetTextSize(50);
	uiScore->SetTextColor(sf::Color::White);
	uiScore->SetPosition({ 20.f, 20.f });

	uiTimebar->Set({ 500.f, 100.f }, sf::Color::Blue);
	uiTimebar->SetOrigin(Origins::ML);
	uiTimebar->SetPosition({ 1920 / 2 - 250.f , 1080.f - 100.f });
}

void SceneDev1::Enter()
{

	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/bee.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	player->SetSceneGame(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneDev1::Exit()
{
	player->SetSceneGame(nullptr);

	Scene::Exit();
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/bee.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneDev1::Status::Game:
		UpdateGame(dt);
		break;
	case SceneDev1::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneDev1::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneDev1::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!");
		score = 0;
		timer = gameTime;
		uiScore->SetScore(score);
		uiTimebar->SetValue(1.f);
		break;
	case SceneDev1::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			score = 0;
			timer = gameTime;
			uiScore->SetScore(score);
			uiTimebar->SetValue(1.f);
			
			player->Reset();
			tree->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneDev1::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case SceneDev1::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Pause! Press ESC To Resume!");
		break;
	}
}

void SceneDev1::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	timer = Utils::Clamp(timer - dt, 0.f, gameTime);

	uiTimebar->SetValue(timer / gameTime);
	if (timer <= 0.f)
	{
		player->OnDie();
		SetCenterMessage("Time Over..");
		SetStatus(Status::GameOver);
		return;
	}
}

void SceneDev1::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::OnChop(Sides side)
{
	Sides branchSide = tree->Chop(side);
	if (player->GetSide() == branchSide)
	{
		player->OnDie();
		SetCenterMessage("You Die!");
		SetStatus(Status::GameOver);
	}
	else
	{
		timer += 1.f;
		score += 100;
		uiScore->SetScore(score);
	}
}

void SceneDev1::OnPlayerDie()
{
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev1::SetCenterMessage(const std::string& msg)
{
	centerMsg->SetString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneDev1::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}
