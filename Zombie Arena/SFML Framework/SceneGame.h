#pragma once
#include "Scene.h"
class PlayerGo;
class SceneGame : public Scene
{
protected:
	PlayerGo* player = nullptr;
public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

