#include "stdafx.h"
#include "CloudGo.h"

CloudGo::CloudGo(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name), speedRange(100.f, 200.f), rangeScale(1.f, 2.f)
{
}

void CloudGo::Update(float dt)
{
	SetPosition(position + speed * dt);
	if (position.x < bounds.x || position.x > bounds.y)
	{
		Reset();
	}
}

void CloudGo::Reset()
{
	SpriteGo::Reset();
	// ¹æÇâ
	if (Utils::RandomValue() >= 0.5f)
	{
		speed.x = Utils::RandomRange(speedRange.x, speedRange.y);
		float randomScale = Utils::RandomRange(rangeScale.x, rangeScale.y);
		SetScale({ randomScale, randomScale });
		SetPosition({ bounds.x, Utils::RandomRange(100.f, 540.f) });
		SetOrigin(Origins::MC);
	}
	else
	{
		speed.x = -Utils::RandomRange(speedRange.x, speedRange.y);
		float randomScale = Utils::RandomRange(rangeScale.x, rangeScale.y);
		SetScale({ -randomScale, randomScale });
		SetPosition({ bounds.y, Utils::RandomRange(100.f, 540.f) });
		SetOrigin(Origins::MC);
	}
}
