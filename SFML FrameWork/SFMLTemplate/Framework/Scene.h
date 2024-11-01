#pragma once
class Scene
{
protected:
	const SceneIds id;
	std::list<GameObject*> gameObjects;

	std::list<GameObject*> addgameObjects;
	std::list<GameObject*> removegameObjects;
public:
	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	 
	virtual void OnPreDraw();
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnPostDraw();
	virtual void RemoveGo(GameObject* obj);

	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list <GameObject*>& list);
	template<typename T>
	T* AddGo(T* obj)
	{
		//if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		//{
		//	gameObjects.push_back(obj);
		//}
		addgameObjects.push_back(obj);
		return obj;

	}
	void ApplyAddGo();
	void ApplyRemoveGo();
};


