#include "stdafx.h"
#include "BranchGo.h"

BranchGo::BranchGo(const std::string& texId, const std::string& name)
	:SpriteGo (texId, name)
{
	SetScale({ 1.f, 1.f });
}

void BranchGo::Reset()
{
	SpriteGo::Reset();
}

void BranchGo::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::Left:
		SetActive(true);
		FlipX(true);
		break;
	case Sides::Right:
		SetActive(true);
		FlipX(false);
		break;
	default:
		SetActive(false);
		break;
	}
}
