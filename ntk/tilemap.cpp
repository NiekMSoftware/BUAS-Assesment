#include "precomp.h"

#include "tilemap.h"
#include <iostream>

#include "json.hpp"
using json = nlohmann::json;

TileMap::TileMap(const char* fileName)
: m_mapWidth(0), m_mapHeight(0)
{
	p_tiles = new Surface(fileName);
	if (!p_tiles)
		printf("TileMap - Couldn't find file: %s", fileName);
}

void TileMap::DrawMap(Surface* screen)
{
	/* 
	  The way how I discovered this lambda expression was via this link:
	  https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
	*/
	auto drawTileAtPosition = [this, screen](int tileId, int screenX, int screenY)
		{
			if (tileId != 0) {
				int tx = (tileId - 1) % (p_tiles->width / m_tileWidth);
				int ty = (tileId - 1) / (p_tiles->width / m_tileHeight);

				DrawTile(tx, ty, screen, screenX, screenY);
			}
		};

	for (const auto& layer : m_layers)
	{
		for (int row = 0; row < m_mapHeight; ++row) {
			int screenY = row * m_tileHeight;
			for (int col = 0; col < m_mapWidth; ++col) {
				int screenX = col * m_tileWidth;
				int tileId = layer[row][col];
				drawTileAtPosition(tileId, screenX, screenY);
			}
		}
	}
}

void TileMap::DrawTile(int tx, int ty, Surface* screen, int x, int y)
{
	uint* src = p_tiles->pixels + PADDING + tx * (m_tileWidth + PADDING) + (PADDING + ty * (m_tileHeight + PADDING)) * p_tiles->width;
	uint* dst = screen->pixels + x + y * screen->width; 

	// precompute strides to increase performance
	const int src_stride = p_tiles->width - m_tileWidth;
	const int dst_stride = screen->width - m_tileWidth;

	for (int i = 0; i < m_tileHeight; ++i)
	{
		for (int j = 0; j < m_tileWidth; ++j)
			dst[j] = src[j];

		// Move to the next row in both source and destination
		src += m_tileWidth + src_stride;
		dst += m_tileWidth + dst_stride;
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
	m_tileWidth = j["tilewidth"];
	m_tileHeight = j["tileheight"];
	m_layers.clear();

	// load tile layers
	for (auto& layer : j["layers"]) 
	{
		if (layer["type"] == "tilelayer") 
		{
			const std::vector<int>& data = layer["data"]; 
			std::vector<std::vector<int>> layerMap(m_mapHeight, std::vector<int>(m_mapWidth));

			// chat gpt helped with the original bug in this.
			for (int row = 0; row < m_mapHeight; ++row) 
			{
				for (int col = 0; col < m_mapWidth; ++col)
					layerMap[row][col] = data[row * m_mapWidth + col];
			}

			m_layers.push_back(layerMap);
		}
	}

	f.close();
	return true;
}

void TileMap::SpawnPlayer(Player* player, int startX, int startY)
{
	player->SpawnAt(startX, startY);
}
