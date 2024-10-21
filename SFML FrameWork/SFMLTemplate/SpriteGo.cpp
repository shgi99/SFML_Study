#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId) :textureId(texId)
{
}

void SpriteGo::Reset()
{
	auto& texResMgr = ResourceMgr<sf::Texture>::Instance();

	sprite.setTexture(texResMgr.Get(textureId));
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
