#include "stdafx.h"
#include "BatGo.h"

BatGo::BatGo(const std::string& name)
	: GameObject(name)
{
}

void BatGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(pos);
}

void BatGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void BatGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if(originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BatGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BatGo::Init()
{
	body.setSize(sf::Vector2f(100.f, 5.f));
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::TC);

	auto windowSize = FRAMEWORK.GetWindowSizeF();
	initPos.x = windowSize.x * 0.5f;
	initPos.y = windowSize.y - 20.f;

	auto halfWidth = body.getSize().x * 0.5f;
	minX = halfWidth;
	maxX = windowSize.x - halfWidth;
}

void BatGo::Reset()
{
	direction = sf::Vector2f(0.f, 0.f);
	SetPosition(initPos);
	isGameOver = false;
}

void BatGo::Update(float dt)
{
	if (isGameOver)
	{
		return;
	}

	direction.x = InputMgr::GetAxis(Axis::Horizontal);

	auto newPos = position + direction * speed * dt;
	newPos.x = Utils::Clamp(newPos.x, minX, maxX);
	SetPosition(newPos);
}

void BatGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(body);
}
