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
	// �� �簢���� �� ������ ��ġ ������
	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};
	// Ÿ���� �ؽ�ó ��ǥ�� ����, �� Ÿ���� �ٸ��� ���̵��� ������ �ؽ�ó ��ǥ�� ���
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
			// �ܰ��� ��� �� �ؽ���
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			// ���� Ÿ���� �ε���
			int quadIndex = i * count.x + j;
			// ���� Ÿ���� ��ǥ(���� ������� ����)
			sf::Vector2f quadPos(j * size.x, i * size.y );

			// �簢���� ��Ÿ���� ���� 4���� ������ �����Ͽ� �ؽ��� �׸�
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;
				// �� Ÿ�� ���� ��ġ������ ���� ��ġ ����
				va[vertexIndex].position = quadPos + posOffset[k];
				// �ؽ�ó ��ǥ ����
				va[vertexIndex].texCoords = texCoords[k];
				// � �ؽ�ó ���� ����Ұ��� ���� 
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::UpdateTransform()
{
}
