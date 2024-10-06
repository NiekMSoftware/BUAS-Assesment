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

TileMap::~TileMap() 
{
	delete m_tiles;
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
	for (int i = 0; i < TILESIZE; i++, src += m_tiles->width, dst += screen->width)
		for (int j = 0; j < TILESIZE; j++)
			dst[j] = src[j];
}

/*
Resources for how I did this can be found here:
https://www.geeksforgeeks.org/how-to-read-from-a-file-in-cpp/
*/ 
void TileMap::LoadMap(const char* mapFile)
{
	std::ifstream file(mapFile);

	if (!file.is_open()) {
		printf("Unable to open file!\n");
		return;
	}

	std::string line;

	// Reading the file line by line
	while (std::getline(file, line)) {
		std::vector<char> tileRow;

		// Reading each character (column) in the line
		for (int col = 0; col < line.size(); ++col, ++m_mapHeight) // also increment map height to speed up the process
		{
			char c = line[col];
			tileRow.push_back(c);
		}

		m_tileMap.push_back(tileRow);
		m_mapWidth++; // add to the width
	}

	file.close();
}