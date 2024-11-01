#include "stdafx.h"
#include "UIScore.h"

UIScore::UIScore(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = -1;

}

void UIScore::Reset()
{
	TextGo::Reset();
	SetScore(0);
}

void UIScore::SetScore(int score)
{
	this->score = score;
	text.setString(textFormat + std::to_string(this->score));
	SetOrigin(originPreset);
}
