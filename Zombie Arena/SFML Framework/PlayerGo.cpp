#include "stdafx.h"
#include "PlayerGo.h"
#include "SceneGame.h"
#include "BulletGo.h"
#include "TileMap.h"
#include "ItemGo.h"

PlayerGo::PlayerGo(const std::string& name)
	: GameObject(name)
{
}

void PlayerGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void PlayerGo::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void PlayerGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void PlayerGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void PlayerGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect PlayerGo::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect PlayerGo::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void PlayerGo::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	
	body.setTexture(TEXTURE_MGR.Get(playerTexId));
	SetOrigin(originPreset);
	SetRotation(0.f);
	direction = { 1.f, 0.f };
	countAmmo = 10;
	hp = maxHp;
	shootTimer = shootDelay;
}

void PlayerGo::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = (sf::Vector2f)mousePos;
	if (sceneGame != nullptr)
	{
		mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	}
	look = Utils::GetNormal(mouseWorldPos - position);

	SetRotation(Utils::Angle(look));
	SetPosition(position + direction * speed * dt);

	shootTimer += dt;
	if (shootTimer > shootDelay && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		shootTimer = 0.f;
		Shoot();
	}
	TileMap* tileMap = dynamic_cast<TileMap*>(sceneGame->FindGo("Tile Map"));
	if (tileMap != nullptr)
	{
		sf::FloatRect movableBound = tileMap->GetLocalBounds();
		sf::Vector2f cellSize = tileMap->GetCellSize();
		if (position.x > movableBound.left + movableBound.width - cellSize.x)
		{
			position.x = movableBound.left + movableBound.width - cellSize.x;
		}
		if (position.x < movableBound.left + cellSize.x)
		{
			position.x = movableBound.left + cellSize.x;
		}
		if (position.y > movableBound.top + movableBound.height - cellSize.y)
		{
			position.y = movableBound.top + movableBound.height - cellSize.y;
		}
		if (position.y < movableBound.top + cellSize.y)
		{
			position.y = movableBound.top + cellSize.y;
		}
	}
	debugBox.SetBounds(GetGlobalBounds());
	debugBox.SetOutlineColor(sf::Color::Green);
}

void PlayerGo::FixedUpdate(float dt)
{
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}

void PlayerGo::Shoot()
{
	if(countAmmo > 0)
	{
		BulletGo* bullet = sceneGame->TakeBullet();
		bullet->Fire(position, look, 800.f, 10);
		countAmmo--;
	}
}

void PlayerGo::OnDamage(int d)
{
	hp -= d;
	std::cout << "Player Damaged! " << hp << std::endl;
}

void PlayerGo::ObtainItem(ItemGo* item)
{
	int itemType = (int)item->GetType();
	switch (itemType)
	{
	case 0:
		countAmmo += 10;
		if (countAmmo > maxAmmo)
		{
			countAmmo = maxAmmo;
		}
		std::cout << "Get Ammo Item " << countAmmo << " Remains." << std::endl;
		break;
	case 1:
		hp += 30;
		if (hp > maxHp)
		{
			hp = maxHp;
		}
		std::cout << "Get Health Item " << hp << " Remains." << std::endl;
		break;
	}
}

