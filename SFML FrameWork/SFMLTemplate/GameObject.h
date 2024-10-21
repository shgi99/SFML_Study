#pragma once
class GameObject
{
protected:
	bool active = true;
	sf::Vector2f position;
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }
	sf::Vector2f Getposition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	virtual void Init(); // 생성 시 초기화
	virtual void Release(); // 동적 할당시 사용
	virtual void Reset(); //
	virtual void Update(float dt); // 활성, 비활성된 객체 업데이트 유무
	virtual void Draw(sf::RenderWindow& window);
};

