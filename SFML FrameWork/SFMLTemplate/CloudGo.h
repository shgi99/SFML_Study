#pragma once
#include "SpriteGo.h"
class CloudGo : public SpriteGo
{
protected:
	sf::Vector2f speed;
	sf::Vector2f speedRange;
	sf::Vector2f bounds;
	sf::Vector2f rangeScale;
public:
	CloudGo(const std::string& texId, const std::string& name = "");
	~CloudGo() = default;

	void SetSpeedRange(const sf::Vector2f speed) { speedRange = speed; }
	void SetBounds(const sf::Vector2f bounds) { this->bounds = bounds; }
	void SetRangeScale(const sf::Vector2f rangeScale) { this->rangeScale = rangeScale; }

	void Update(float dt) override;
	void Reset() override;

};
