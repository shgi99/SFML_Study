#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name) 
	:GameObject(name), textureId(texId)
{
}

void SpriteGo::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(originPreset);
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(sprite);
}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void SpriteGo::SetScale(const sf::Vector2f& newScale)
{
	GameObject::SetScale(newScale);
	sprite.setScale(newScale);
}
