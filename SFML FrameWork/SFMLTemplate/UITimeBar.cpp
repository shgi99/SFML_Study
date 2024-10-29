#include "stdafx.h"
#include "UITimeBar.h"

UITimeBar::UITimeBar(const std::string& name)
	:GameObject(name)
{
}

void UITimeBar::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(pos);
}

void UITimeBar::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(shape, originPreset);
	}
}

void UITimeBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	shape.setOrigin(origin);
}

void UITimeBar::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	shape.setScale(this->scale);
}

void UITimeBar::Init()
{
}

void UITimeBar::Release()
{
}

void UITimeBar::Reset()
{
}

void UITimeBar::Update(float dt)
{
}

void UITimeBar::Draw(sf::RenderWindow& window)
{

	window.draw(shape);
}

void UITimeBar::Set(const sf::Vector2f size, const sf::Color& color)
{
	currentSize = maxSize = size;
	shape.setFillColor(color);
	SetValue(1.f);
	SetOrigin(originPreset);
	std::cout << "UITimeBar maxSize set to: " << maxSize.x << ", " << maxSize.y << std::endl;
}

void UITimeBar::SetValue(float value)
{
	value = Utils::Clamp(value, 0.f, 1.f);
	currentSize.x = maxSize.x * value;
	shape.setSize(currentSize);
	SetOrigin(originPreset);
}
