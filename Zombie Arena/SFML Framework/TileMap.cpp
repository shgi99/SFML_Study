#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{

}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	transform.translate(position);
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	transform.rotate(rotation);
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	transform.scale(scale);
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
	origin = newOrigin;
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	Set({ 28, 28 }, { 50.f, 50.f });
	SetOrigin(Origins::TL);
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(tileMapTexId);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	SetOrigin(originPreset);
	SetScale({ 1.0f, 1.0f });
	SetPosition({ 0.f, windowSize.y * 0.5f });
	SetRotation(-45.f);
	
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates states;
	states.texture = texture;
	states.transform = transform;
	window.draw(va, states);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f tilePosOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};

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
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j * size.x, i * size.y);

			// 사각형을 나타내기 위해 4개의 정점을 생성하여 텍스쳐 그림
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;
				// 각 타일 기준 위치에서의 정점 위치 설정
				va[vertexIndex].position = quadPos + tilePosOffset[k];
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
