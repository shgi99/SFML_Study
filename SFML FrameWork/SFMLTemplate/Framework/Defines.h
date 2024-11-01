#pragma once
enum class SortingLayers
{
	Background,
	Foreground,
	UI,
	Default,
};
enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
	Count
};

enum class Origins
{
	// TOP MIDDLE BOTTOM
	// LEFT CENTER RIGHT
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};