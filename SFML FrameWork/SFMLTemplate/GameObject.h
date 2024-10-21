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

	virtual void Init(); // ���� �� �ʱ�ȭ
	virtual void Release(); // ���� �Ҵ�� ���
	virtual void Reset(); //
	virtual void Update(float dt); // Ȱ��, ��Ȱ���� ��ü ������Ʈ ����
	virtual void Draw(sf::RenderWindow& window);
};

