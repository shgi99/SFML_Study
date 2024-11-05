#include "stdafx.h"
#include "SceneGame.h"
#include "PlayerGo.h"
#include "TileMap.h"
SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Tile Map"));

	player = AddGo(new PlayerGo("Player"));
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}
