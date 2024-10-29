#pragma once
#include "GameObject.h"
class UITimeBar : public GameObject
{
protected:
	sf::RectangleShape shape;
	sf::Vector2f maxSize;
	sf::Vector2f currentSize;
public:
	UITimeBar(const std::string& name = "");
	virtual ~UITimeBar() = default;
	
	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Init() override; // 생성 시 초기화
	void Release() override; // 동적 할당시 사용
	void Reset() override; //

	void Update(float dt) override; // 활성, 비활성된 객체 업데이트 유무
	void Draw(sf::RenderWindow& window) override;
	void Set(const sf::Vector2f size, const sf::Color& color);

	float GetValue() const { return currentSize.x / maxSize.x; }
	void SetValue(float value);
};

