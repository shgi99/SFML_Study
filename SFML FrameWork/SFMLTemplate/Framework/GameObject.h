#pragma once

class GameObject
{
protected:
	std::string name;

	bool active = true;

	sf::Vector2f position;
	sf::Vector2f scale;

	Origins originPreset;
	sf::Vector2f origin;
public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f Getposition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}
	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& scale) { this->scale = scale; }
	virtual void SetString(const std::string& str = "");
	virtual void FlipX(bool tf);
	virtual void FlipY(bool tf);

	virtual void Init(); // ���� �� �ʱ�ȭ
	virtual void Release(); // ���� �Ҵ�� ���
	virtual void Reset(); //
	virtual void Update(float dt); // Ȱ��, ��Ȱ���� ��ü ������Ʈ ����
	virtual void Draw(sf::RenderWindow& window);
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		if (a->sortingLayer != b->sortingLayer)
		{
			return a->sortingLayer > b->sortingLayer;
		}
		return a->sortingOrder < b->sortingOrder;
	}
};