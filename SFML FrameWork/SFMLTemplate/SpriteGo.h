#pragma once
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;
public:
	SpriteGo() = default;
	~SpriteGo() = default;

	SpriteGo(const std::string& texId = "", const std::string& name = "");
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;

	void SetTextureId(const std::string id) { textureId = id; }

	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);
	virtual void SetScale(const sf::Vector2f& newScale);
};

