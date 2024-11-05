#include "stdafx.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(const std::string& name)
	: GameObject(name)
{
}

void PlayerGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(pos);
}

void PlayerGo::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
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
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(originPreset);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	direction = { 1.f, 0.f };
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

	// 마우스 방향으로 캐릭터가 바라보게 하는 하도록 Rotate하는 함수
	auto mousePos = (sf::Vector2f) InputMgr::GetMousePosition();
	look = Utils::GetNormal(mousePos - position);
	SetRotation(Utils::Angle(look));

	SetPosition(position + direction * speed * dt);
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
