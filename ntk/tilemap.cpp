#include "precomp.h"

#include "tilemap.h"
#include <iostream>

#include "json.hpp"
using json = nlohmann::json;

TileMap::TileMap(const char* fileName)
: m_mapWidth(0), m_mapHeight(0)
{
	m_tiles = new Surface(fileName);
	if (!m_tiles)
		printf("TileMap - Couldn't find file: %s", fileName);
}

void TileMap::DrawMap(Surface* screen)
{
	for (int y = 0; y < m_tileMap.size(); ++y)
	{
		for (int x = 0; x < m_tileMap[y].size(); ++x)
		{
			int tileId = m_tileMap[y][x];

			// only draw if the tile isn't empty
			if (tileId != 0) {
				int tx = (tileId - 1) % (m_tiles->width / TILESIZE);
				int ty = (tileId - 1) / (m_tiles->width / TILESIZE);
				int screenX = x * TILESIZE;
				int screenY = y * TILESIZE;

				// Draw the tile at the correct screen position.
				DrawTile(tx, ty, screen, screenX, screenY);
			}
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
			dst[j] = src[j];

		// Move to the next row in both source and destination
		src += TILESIZE + src_stride;
		dst += TILESIZE + dst_stride;
	}
}

bool TileMap::LoadJSONMap(const char* file)
{
	std::ifstream f(file);
	if (!f.is_open()) {
		std::cerr << "Unable to find file: " << file << '\n';
		return false;
	}

	// parse the json file
	json j;
	f >> j;

	// extract width and height
	m_mapWidth = j["width"];
	m_mapHeight = j["height"];

	printf("m_mapWidth: %d\n", m_mapWidth);
	printf("m_mapHeight: %d\n", m_mapHeight);

	// load tile layers
	for (auto& layer : j["layers"]) 
	{
		if (layer["type"] == "tilelayer") 
		{
			const std::vector<int>& data = layer["data"]; 
			m_tileMap.resize(m_mapHeight);

			// chat gpt helped with the original bug in this.
			for (int row = 0; row < m_mapHeight; ++row) 
			{
				m_tileMap[row].resize(m_mapWidth);
				for (int col = 0; col < m_mapWidth; ++col)
					m_tileMap[row][col] = data[row * m_mapWidth + col];
			}
		}
	}

	f.close();
	return true;
}

void TileMap::SpawnPlayer(Player* player, int startX, int startY)
{
	player->SpawnAt(startX, startY, TILESIZE);
}
