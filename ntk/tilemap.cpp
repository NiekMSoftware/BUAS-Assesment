#include "precomp.h"
#include "tilemap.h"

#include <iostream>

TileMap::TileMap(const char* tilesetPath, int mapWidth, int mapHeight, int frameCount)
: m_width(mapWidth), m_height(mapHeight)
{
	// create sprites based on the tileset
	Surface* tilesetSurface = new Surface(tilesetPath);

	for (int i = 0; i < frameCount; i++)
	{
		Sprite* tileSprite = new Sprite(tilesetSurface, frameCount);
		m_tileSprites.push_back(tileSprite);
	}

	// init map size
	m_map.resize(m_height, std::vector<int>(m_width, 0));
}

TileMap::~TileMap()
{
	for (auto* sprite : m_tileSprites) delete sprite;
}

void TileMap::DrawMap(Surface* screen, int offsetX, int offsetY)
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int tileIndex = m_map[y][x];
			Sprite* tileSprite = m_tileSprites[tileIndex];

			tileSprite->Draw(screen, x * SPRITESIZE + offsetX, y * SPRITESIZE + offsetY);
		}
	}
}

bool TileMap::LoadMap(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cout << "Unable to locate map file at " + filePath << '\n';
		return false;
	}

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int tileType;
			file >> tileType;
			m_map[y][x] = tileType;
		}
	}
	
	file.close();
	return true;
}

bool TileMap::CheckPos(int x, int y)
{
	int tx = x / SPRITESIZE, ty = y / SPRITESIZE;
	return m_map[ty][tx] != 1;	// might have to replace 1
}
