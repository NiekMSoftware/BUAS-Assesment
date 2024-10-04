#include "precomp.h"
#include "tilemap.h"

TileMap::TileMap(const char* fileName, int mapWidth, int mapHeight)
: m_mapWidth(mapWidth * TILESIZE), m_mapHeight(mapHeight * TILESIZE)
{
	m_tiles = new Surface(fileName);
	if (!m_tiles)
		std::runtime_error("Could not find file: " + std::string(fileName));
}

TileMap::~TileMap() 
{
	delete m_tiles;
}

void TileMap::DrawMap(int mapWidth, int mapHeight, Surface* screen)
{
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			// int tx = m_tileMap[y][x * 3] - 'a';
			// int ty = m_tileMap[y][x * 3 + 1] - 'a';
			// DrawTile(tx, ty, screen, x * TILESIZE, y * TILESIZE);
		}
	}
}

void TileMap::DrawTile(int tx, int ty, Surface* screen, int x, int y)
{
	uint* src = m_tiles->pixels + PADDING + tx * (TILESIZE + PADDING) + (PADDING + ty * (TILESIZE + 1)) * 595;
	uint* dst = screen->pixels + x + y * 800;
	for (int i = 0; i < TILESIZE; i++, src += 595, dst += 800)
		for (int j = 0; j < TILESIZE; j++)
			dst[j] = src[j];
}
