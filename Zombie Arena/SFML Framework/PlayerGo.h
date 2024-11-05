#pragma once

class PlayerGo : public GameObject
{
protected:
	sf::Sprite body;
	std::string playerTexId = "graphics/player.png";

	float speed = 300.f;
	sf::Vector2f direction;
	sf::Vector2f look;
public:
	PlayerGo(const std::string& name = "");
	~PlayerGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
