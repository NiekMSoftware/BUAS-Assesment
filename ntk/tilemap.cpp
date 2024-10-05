#include "precomp.h"
#include "tilemap.h"

#include <sstream>
#include <iostream>

TileMap::TileMap(const char* fileName, int mapWidth, int mapHeight, int tileSetWidth)
: m_mapWidth(mapWidth * TILESIZE), m_mapHeight(mapHeight * TILESIZE), m_tilesetWidth(tileSetWidth)
{
	m_tiles = new Surface(fileName);
	if (!m_tiles)
		std::runtime_error("Could not find file: " + std::string(fileName));
}

TileMap::~TileMap() 
{
	delete m_tiles;
}

void TileMap::DrawMap(Surface* screen)
{
	for (int y = 0; y < m_tileMap.size(); y++)
	{
		for (int x = 0; x < m_tileMap[y].size(); x++)
		{
			char tileChar = m_tileMap[y][x];

			int tx = (tileChar - 'a') % m_tilesetWidth;
			int ty = (tileChar - 'a') / m_tilesetWidth;
			DrawTile(tx, ty, screen, x * TILESIZE, y * TILESIZE);
		}
	}
}

void TileMap::DrawTile(int tx, int ty, Surface* screen, int x, int y)
{
	uint* src = m_tiles->pixels + PADDING + tx * (TILESIZE + PADDING) + (PADDING + ty * (TILESIZE + PADDING)) * 595;
	uint* dst = screen->pixels + x + y * screen->width;
	for (int i = 0; i < TILESIZE; i++, src += 595, dst += screen->width)
		for (int j = 0; j < TILESIZE; j++)
			dst[j] = src[j];
}

void TileMap::LoadMap(const char* mapFile)
{
	std::ifstream file("assets/maps/map.txt");

	if (!file.is_open()) {
		printf("Unable to open file!\n");
		return;
	}

	std::string line;
	int row = 0;

	// Reading the file line by line
	while (std::getline(file, line)) {
		std::vector<char> tileRow;

		// Reading each character (column) in the line
		for (int col = 0; col < line.size(); ++col) {
			char c = line[col];
			tileRow.push_back(c);
			//printf("Character at Row %i, Column %i: %c (ASCII: %i)\n", row, col, c, static_cast<int>(c));
		}

		m_tileMap.push_back(tileRow);
		row++;  // Increment row for the next line
	}

	file.close();
}

void TileMap::ReadMap()
{
	for (int y = 0; y < m_tileMap.size(); y++) {
		for (int x = 0; x < m_tileMap[y].size(); x++) {
			std::cout << m_tileMap[y][x];
		}
		std::cout << std::endl;  // Newline after each row
	}
}