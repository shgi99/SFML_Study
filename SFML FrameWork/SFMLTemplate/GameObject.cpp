#include "stdafx.h"
#include "GameObject.h"



GameObject::GameObject(const std::string& name) : name(name), originPreset(Origins::TL), origin(0.f, 0.f)
{
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::SetString(const std::string& str)
{
}

void GameObject::FlipX(bool tf)
{
	if (tf == true)
	{
		SetScale({ -GetScale().x, GetScale().y});
	}
	else
	{
		SetScale({ GetScale().x, GetScale().y });
	}
	return;
}

void GameObject::FlipY(bool tf)
{
	if (tf == true)
	{
		SetScale({ GetScale().x, -GetScale().y });
	}
	else
	{
		SetScale({ GetScale().x, GetScale().y });
	}
	return;
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}
