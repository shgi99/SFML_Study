#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	Set({ 10, 10 }, { 50.f, 50.f });
	SetOrigin(Origins::TL);
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(originPreset);
	SetPosition({ 0.f, 0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);
	// 각 사각형의 각 정점의 위치 오프셋
	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};
	// 타일의 텍스처 좌표를 정의, 각 타일이 다르게 보이도록 임의의 텍스처 좌표를 사용
	sf::Vector2f texCoords[4] =
	{
		{0.f, 0.f},
		{50.f, 0.f},
		{50.f, 50.f},
		{0.f, 50.f}
	};

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex = Utils::RandomRange(0, 2);
			// 외곽일 경우 벽 텍스쳐
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			// 현재 타일의 인덱스
			int quadIndex = i * count.x + j;
			// 현재 타일의 좌표(좌측 상단으로 설정)
			sf::Vector2f quadPos(j * size.x, i * size.y );

			// 사각형을 나타내기 위해 4개의 정점을 생성하여 텍스쳐 그림
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;
				// 각 타일 기준 위치에서의 정점 위치 설정
				va[vertexIndex].position = quadPos + posOffset[k];
				// 텍스처 좌표 설정
				va[vertexIndex].texCoords = texCoords[k];
				// 어떤 텍스처 패턴 사용할건지 적용 
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::UpdateTransform()
{
}
