#include "stdafx.h"
#include "SceneGame.h"
#include "BatGo.h"
#include "BallGo.h"
#include "TextGo.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	auto windowSize = FRAMEWORK.GetWindowSizeF();
	bat = AddGo(new BatGo("Bat"));
	ball = AddGo(new BallGo("Ball"));
	ball->SetBat(bat);
	gameoverText = AddGo(new TextGo("fonts/HeirofLightBold.ttf"));
	gameoverText->SetString("Press Space To Start !!");
	gameoverText->SetPosition({ windowSize.x / 2,windowSize.y / 2 });
	gameoverText->SetOrigin(Origins::MC);
	gameoverText->SetScale({ 2.f,2.f });
	gameoverText->SetActive(false);

	scoreText = AddGo(new TextGo("fonts/HeirofLightBold.ttf"));
	scoreText->SetString("Score :" + std::to_string(score));
	scoreText->SetOrigin(Origins::TL);
	scoreText->SetPosition({ 50.f, 50.f });
	scoreText->SetScale({ 1.5f,1.5f });
	scoreText->SetActive(true);
	Scene::Init();
}

void SceneGame::Enter()
{
	FONT_MGR.Load("fonts/HeirofLightBold.ttf");
	Scene::Enter();
	ball->SetScore(0);
	gameoverText->SetActive(false);
	isBallActive = false;
	ball->SetGameOver(false);
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGame::Exit()
{
	FONT_MGR.Unload("fonts/HeirofLightBold.ttf");
}

void SceneGame::Update(float dt)
{
	if (score != ball->GetScore())
	{
		score = ball->GetScore();
		scoreText->SetString("Score :" + std::to_string(score));
	}
	if (!isBallActive)
	{
		ball->SetPosition(bat->GetPosition());
	}
	if (ball->IsGameOver())
	{
		gameoverText->SetString("\t\t   Game Over\nPress Enter To Replay !");
		gameoverText->SetActive(true);
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		return;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		if (!isBallActive)
			ball->Fire({ 1.f,-1.f }, 500.f);
		isBallActive = true;
	}

	if (InputMgr::GetKey(sf::Keyboard::Z))
	{
		FRAMEWORK.SetTimeScale(3.f);
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Z))
	{
		FRAMEWORK.SetTimeScale(1.f);
	}
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

