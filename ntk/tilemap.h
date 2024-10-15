#pragma once

#define PADDING 1

class TileMap
{
	// TODO: Add a struct named Tile, instead of char's.
public:
	TileMap(const char* fileName);
	~TileMap() = default;

	void DrawMap(Surface* screen);
	bool LoadJSONMap(const char* file);

	void SpawnPlayer(Player* player, int startX, int startY);
private:
	void DrawTile(int tx, int ty, Surface* screen, int x, int y);

private:
	// tile properties
	int m_tileWidth = 0, m_tileHeight = 0;
	int m_mapWidth, m_mapHeight;
	Surface* p_tiles;

	// tilemap 2-/3-dimensional arrays
	std::vector<std::vector<int>> m_tileMap;
	std::vector<std::vector<std::vector<int>>> m_layers;
};