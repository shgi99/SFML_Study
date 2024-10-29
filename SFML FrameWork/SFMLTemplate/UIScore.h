#pragma once
#include "TextGo.h"
class UIScore : public TextGo
{
protected:
	std::string textFormat = "SCORE: ";
	int score = 0;
public:
	~UIScore() = default;
	UIScore(const std::string& fontId, const std::string& name = "");

	void Reset();
	void SetScore(int score);
};

