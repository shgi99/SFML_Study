#pragma once
#include "GameObject.h"
#include "SceneDev1.h"
class SceneDev1;
class PlayerGo : public GameObject
{
protected:
	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;
	sf::Sprite spriteRip;

	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";

	Sides playerSide = Sides::Right;

	sf::Vector2f localPosPlayer[3] = { {-300.f, 0.f}, {300.f, 0.f}, {0.f, 0.f} };
	sf::Vector2f localPosAxe = { 0.f, -70.f };
	sf::Vector2f localPosRip = { 0.f, 0.f };

	sf::Vector2f originAxe = { -60.f, 0.f };

	bool isAlive = true;
	bool isChopping = false;

	SceneDev1* sceneGame;
public:
	PlayerGo(const std::string& name = "");
	virtual ~PlayerGo() = default;

	Sides GetSide() const { return playerSide; }
	void SetSide(Sides s);
	void OnDie();

	void SetPosition(const sf::Vector2f& pos);
	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	void SetScale(const sf::Vector2f& scale);

	void Init() override; // ���� �� �ʱ�ȭ
	void Release() override; // ���� �Ҵ�� ���
	void Reset() override; //
	void Update(float dt) override; // Ȱ��, ��Ȱ���� ��ü ������Ʈ ����
	void Draw(sf::RenderWindow& window) override;
	void SetSceneGame(SceneDev1* scene);
};


