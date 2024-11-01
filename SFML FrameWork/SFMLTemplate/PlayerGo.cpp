#include "stdafx.h"
#include "PlayerGo.h"
#include "SceneDev1.h"
PlayerGo::PlayerGo(const std::string& name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
 
}

void PlayerGo::SetSide(Sides s)
{
	playerSide = s;
	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	
	if (playerSide == Sides::Left)
	{
		SetScale({ -1.f, 1.f });
	}
	else if(playerSide == Sides::Right)
	{
		SetScale({ 1.f, 1.f });
	}

	spritePlayer.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localPosRip);
}

void PlayerGo::OnDie()
{
	isAlive = false;
	
}

void PlayerGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(playerSide);

}

void PlayerGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
	}
}

void PlayerGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
}

void PlayerGo::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f ripScale = this->scale;
	ripScale.x = abs(axeScale.x);
	spriteRip.setScale(ripScale);
}

void PlayerGo::Init()
{
	GameObject::Init();
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);

}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{	
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	isAlive = true;
	isChopping = false;
	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);
}

void PlayerGo::Update(float dt)
{
	if (!isAlive)
		return;
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		isChopping = true;
		SetSide(Sides::Left);
		sceneGame->OnChop(Sides::Left);
		sfxChop.play();
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Left))
	{
		isChopping = false;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		isChopping = true;
		SetSide(Sides::Right);
		sceneGame->OnChop(Sides::Right);
		sfxChop.play();
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		isChopping = false;
	}
	if (!isAlive)
	{
		return;
	}
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	if (isAlive)
	{
		window.draw(spritePlayer);
		if (isChopping)
		{
			window.draw(spriteAxe);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void PlayerGo::SetSceneGame(SceneDev1* scene)
{
	sceneGame = scene;
}
