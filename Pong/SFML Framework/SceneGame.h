#pragma once
#include "Scene.h"
class BatGo;
class BallGo;
class TextGo;
class SceneGame : public Scene
{
protected:
	BatGo* bat = nullptr;
	BallGo* ball = nullptr;
	TextGo* gameoverText;
	TextGo* scoreText;

	int score = 0;

	bool isBallActive;
public:
	SceneGame();
	~SceneGame() = default;

	void Init();
	void Enter();
	void Exit() override;
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void setScore();
};

