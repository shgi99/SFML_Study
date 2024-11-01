#pragma once
#include "Scene.h"
class BatGo;
class BallGo;
class SceneGame : public Scene
{
protected:
	BatGo* bat = nullptr;
	BallGo* ball = nullptr;

	bool isBallActive;
public:
	SceneGame();
	virtual ~SceneGame() = default;

	virtual void Init();
	virtual void Enter();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

