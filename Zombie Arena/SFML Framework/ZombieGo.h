#pragma once
class PlayerGo;
class SceneGame;
class ZombieGo : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int zombieTypes = 3;
protected:
	Types types = Types::Bloater;
	sf::Sprite body;
	std::string textureId;

	sf::Vector2f direction;

	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 3.f;
	int hp = 0;
	float attackTimer = 0.f;

	PlayerGo* player;
	SceneGame* sceneGame;
	DebugBox debugBox;
public:
	ZombieGo(const std::string& name = "");
	~ZombieGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);

	void OnDamage(int damage);
};