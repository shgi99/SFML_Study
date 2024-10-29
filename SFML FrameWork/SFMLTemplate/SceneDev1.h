#pragma once
#include "Scene.h"

class TreeGo;
class PlayerGo;
class SceneDev1 : public Scene
{
protected:
	TreeGo* tree;
	PlayerGo* player;
public:
	SceneDev1();
	~SceneDev1() = default;
	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

