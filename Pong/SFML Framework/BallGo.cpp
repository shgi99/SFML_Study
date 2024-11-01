#include "stdafx.h"
#include "BallGo.h"

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

	movableBounds = FRAMEWORK.GetWindowBounds();
	movableBounds.left += halfWidth;
	movableBounds.width -= radius;
	movableBounds.top += radius * 2.f;
	movableBounds.height -= radius * 2.f;
}

void BallGo::Reset()
{
	direction = sf::Vector2f(0.f, 0.f);
	speed = 0.f;
}

void BallGo::Update(float dt)
{
	auto newPos = position + direction * speed * dt;
	SetPosition(newPos);
}

void BallGo::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
