#pragma once
#include "Scene.h"

class TreeGo;
class PlayerGo;
class TextGo;
class UIScore;
class UITimeBar;
class SceneDev1 : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};
protected:
	TreeGo* tree;
	PlayerGo* player;
	TextGo* centerMsg;
	UIScore* uiScore;
	UITimeBar* uiTimebar;

	Status currentStatus;
	int score = 0;
	float timer = gameTime;
	float gameTime = 5.f;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;
	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";
public:
	SceneDev1();
	~SceneDev1() = default;
	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void SetStatus(Status newStatus);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void OnChop(Sides side);
	void OnPlayerDie();

	void Draw(sf::RenderWindow& window) override;

	void SetCenterMessage(const std::string& msg);
	void SetVisibleCenterMessage(bool visible);
};

