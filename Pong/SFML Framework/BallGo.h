#pragma once
#include "GameObject.h"

class BatGo;
class BallGo : public GameObject
{
protected:
	sf::CircleShape body;
	sf::Vector2f direction;
	float speed = 0.f;

	sf::FloatRect movableBounds;
	BatGo* bat = nullptr;

	int score = 0;
	bool isGameOver = false;
public:
    BallGo(const std::string& name = "");
    virtual ~BallGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire(const sf::Vector2f& d, float s)
	{
		direction = d;
		speed = s;
	}

	void SetBat(BatGo* bat) { this->bat = bat; }
	bool IsGameOver() const { return isGameOver; }
	void SetGameOver(bool isGameOver)
	{
		this->isGameOver = isGameOver;
	}
	void SetScore(int score)
	{
		this->score = score;
	}
	int GetScore()
	{
		return score;
	}
};