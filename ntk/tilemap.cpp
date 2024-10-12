#include "precomp.h"

#include "tilemap.h"

#include <iostream>

TileMap::TileMap(const char* fileName)
: m_mapWidth(0), m_mapHeight(0)
{
	m_tiles = new Surface(fileName);
	if (!m_tiles)
		printf("TileMap - Couldn't find file: %s", fileName);
}

void TileMap::DrawMap(Surface* screen)
{
	for (int y = 0; y < m_tileMap.size(); y++)
	{
		for (int x = 0; x < m_tileMap[y].size() / 3; x++)
		{
			int tx = m_tileMap[y][x * 3] - 'a';
			int ty = m_tileMap[y][x * 3 + 1] - 'a';

			DrawTile(tx, ty, screen, x * TILESIZE, y * TILESIZE);
		}
	}
}

void TileMap::DrawTile(int tx, int ty, Surface* screen, int x, int y)
{
	uint* src = m_tiles->pixels + PADDING + tx * (TILESIZE + PADDING) + (PADDING + ty * (TILESIZE + PADDING)) * m_tiles->width;
	uint* dst = screen->pixels + x + y * screen->width; 

	// precompute strides to increase performance
	const int src_stride = m_tiles->width - TILESIZE;
	const int dst_stride = screen->width - TILESIZE;

	for (int i = 0; i < TILESIZE; ++i)
	{
		for (int j = 0; j < TILESIZE; ++j)
		{
			dst[j] = src[j];
		}

		src += m_tiles->width;
		dst += screen->width;
	}
}

/*
Resources for how I did this can be found here:
https://www.geeksforgeeks.org/how-to-read-from-a-file-in-cpp/
*/ 
bool TileMap::LoadTextMap(const char* mapFile)
{
	std::ifstream file(mapFile);
	if (!file.is_open()) {
		std::cerr << "Unable to find file: " << mapFile << '\n';
		return false;
	}

	std::string line;
	m_mapHeight = 0;

	// Reading the file line by line
	while (std::getline(file, line)) {
		std::vector<char> tileRow(line.begin(), line.end());
		m_tileMap.push_back(tileRow);
		m_mapHeight++;
	}
	m_mapWidth = !m_tileMap.empty() ? m_tileMap[0].size() : 0;

	file.close();

	return true;
}

void TileMap::SpawnPlayer(Player* player, int startX, int startY)
{
	player->SpawnAt(startX, startY, TILESIZE);
}
