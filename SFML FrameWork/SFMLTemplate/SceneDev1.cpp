#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "CloudGo.h"
#include "BeeGo.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	GameObject* textObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"));
	textObj->SetOrigin(Origins::TL);
	textObj->SetPosition({ 0, 0 });
	textObj->SetString("dev1");

	for (int i = 0; i < 1000; i++)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->SetRangeScale({ 1.f, 2.f });
		cloud->SetBounds({ -300.f, 2220.f });
		cloud->SetPosition({ 0.f, Utils::RandomRange(100.f, 540.f)});

		BeeGo* bee = AddGo(new BeeGo("graphics/bee.png"));
		bee->SetBounds({ -300.f, 2220.f });
		bee->SetPosition({ 0.f, Utils::RandomRange(540.f, 800.f) });
	}

	Scene::Init();
}

void SceneDev1::Enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/bee.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/bee.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");

	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
