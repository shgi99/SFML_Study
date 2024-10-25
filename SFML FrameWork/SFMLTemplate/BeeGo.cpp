#include "stdafx.h"
#include "BeeGo.h"

BeeGo::BeeGo(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name), speedRange(100.f, 200.f)
{
}

void BeeGo::Update(float dt)
{
	SetPosition({ position.x + speed.x * dt,  position.y + (1.f * sin(position.x / 30)) });
	if (position.x < bounds.x || position.x > bounds.y)
	{
		Reset();
	}
}

void BeeGo::Reset()
{
	SpriteGo::Reset();
	// 방향
	if (Utils::RandomValue() >= 0.5f)
	{
		// 위치
		speed.x = Utils::RandomRange(speedRange.x, speedRange.y);
		SetScale({ -1.f, 1.f });
		SetPosition({ bounds.x, Utils::RandomRange(700.f, 800.f) });
	}
	else
	{
		speed.x = -Utils::RandomRange(speedRange.x, speedRange.y);
		SetScale({ 1.f, 1.f });
		SetPosition({ bounds.y, Utils::RandomRange(700.f, 800.f) });
	}
	SetOrigin(Origins::MC);
}
