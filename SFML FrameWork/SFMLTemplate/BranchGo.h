#pragma once
#include "SpriteGo.h"
class BranchGo : public SpriteGo
{
protected:
	Sides side = Sides::None;

public:
	BranchGo(const std::string& texId, const std::string& name = "");
	~BranchGo() = default;

	void Reset() override;

	void SetSide(Sides side);
	Sides GetSide() const { return side; }

};

