#include "stdafx.h"
#include "SceneGame.h"
#include "BatGo.h"
#include "BallGo.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	bat = AddGo(new BatGo("Bat"));
	ball = AddGo(new BallGo("Ball"));
	ball->SetBat(bat);
	Scene::Init();
}

void SceneGame::Enter()
{
	isBallActive = false;
	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (!isBallActive)
	{
		ball->SetPosition(bat->GetPosition());
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		ball->Fire({ 1.f, -1.f }, 500.f);
		isBallActive = true;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
