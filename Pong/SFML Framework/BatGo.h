#pragma once
#include "GameObject.h"
class BatGo : public GameObject
{
protected:
	sf::RectangleShape body;

	sf::Vector2f direction;
	float speed = 500.f;
	
	sf::Vector2f initPos;

	float minX = 0.f;
	float maxX = 0.f;
public:
	BatGo(const std::string& name = "");
	virtual ~BatGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

