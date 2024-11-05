#include "stdafx.h"
#include "BallGo.h"
#include "BatGo.h"
#include "SceneGame.h"
BallGo::BallGo(const std::string& name)
	: GameObject(name)
{
}

void BallGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void BallGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void BallGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BallGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BallGo::Init()
{
	float radius = 10.f;
	body.setRadius(radius);
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);

	float halfWidth = 5.f;
	//윈도우 바운드와 공 크기에 비례해 무브에이블바운즈를 재설정
	movableBounds = FRAMEWORK.GetWindowBounds();
	movableBounds.left += halfWidth;
	movableBounds.width -= radius;
	movableBounds.top += radius * 2.f;
	//movableBounds.height -= radius * 2.f;
}

void BallGo::Reset()
{
	direction = sf::Vector2f(0.f, 0.f);
	speed = 0.f;
}

void BallGo::Update(float dt)
{
	if (isGameOver)
		return;
	auto newPos = position + direction * speed * dt;

	if (newPos.x < movableBounds.left)
	{
		newPos.x = movableBounds.left;
		direction.x *= -1.f;
	}
	else if (newPos.x > movableBounds.width)
	{
		newPos.x = movableBounds.width;
		direction.x *= -1.f;
	}

	if (newPos.y < movableBounds.top)
	{
		newPos.y = movableBounds.top;
		direction.y *= -1.f;
	}
	else if (newPos.y > movableBounds.height + body.getRadius() * 2)
	{
		/*newPos.y = movableBounds.height;
		direction.y *= -1.f;*/
		SetGameOver(true);
		bat->SetGameover(true);
		speed = 0.f;
	}

	if (bat != nullptr)
	{
		auto batBounds = bat->GetBatBounds();
		if (body.getGlobalBounds().intersects(batBounds))
		{
			score += 100;
			newPos.y = batBounds.top;
			direction.y *= -1.f;
		}
	}

	SetPosition(newPos);
}

void BallGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(body);
}
