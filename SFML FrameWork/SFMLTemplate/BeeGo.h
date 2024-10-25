#pragma once
#include "SpriteGo.h"
class BeeGo :
    public SpriteGo
{
protected:
	sf::Vector2f speed;
	sf::Vector2f speedRange;
	sf::Vector2f bounds;
public:
	BeeGo(const std::string& texId, const std::string& name = "");
	~BeeGo() = default;

	void SetSpeedRange(const sf::Vector2f speed) { speedRange = speed; }
	void SetBounds(const sf::Vector2f bounds) { this->bounds = bounds; }

	void Update(float dt) override;
	void Reset() override;
};

