#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id) : id(id)
{
}

void Scene::Init()
{
	for (auto go : addgameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addgameObjects.clear();

	// 초기에 갖고 있어야하는 GameObject들을 add
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	// Scene이 바뀌고 재시작할때마다 호출되는 함수
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyRemoveGo();
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}

		obj->Update(dt);
	}
}

void Scene::LateUpdate(float dt)
{

}

void Scene::OnPreDraw()
{
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		drawQueue.push(obj);
	}
	while (!drawQueue.empty())
	{
		GameObject* objt = drawQueue.top();
		objt->Draw(window);
		drawQueue.pop();
	}
}

void Scene::OnPostDraw()
{
	for (auto go : addgameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addgameObjects.clear();

	for (auto go : removegameObjects)
	{
		gameObjects.remove(go);
	}
	removegameObjects.clear();
}

void Scene::RemoveGo(GameObject* obj)
{
	removegameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	int cnt = 0;
	list.clear();

	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
			cnt++;
		}
	}
	return cnt;
}

void Scene::ApplyAddGo()
{
	for (auto go : addgameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addgameObjects.clear();
}

void Scene::ApplyRemoveGo()
{
	for (auto go : removegameObjects)
	{
		gameObjects.remove(go);
	}
	removegameObjects.clear();
}
