#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
protected:
	std::string fontId;
	sf::Text text;

public:

	TextGo(const std::string& fontId, const std::string& name = "");
	~TextGo() = default;

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	void SetString(const std::string s);
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Draw(sf::RenderWindow& window) override;
};

