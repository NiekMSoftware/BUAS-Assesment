#pragma once

#define TILESIZE 32
#define PADDING 1

class TileMap
{
	// TODO: Add a struct named Tile, instead of char's.
public:
	TileMap(const char* fileName);
	~TileMap() = default;

	void DrawMap(Surface* screen);
	bool LoadTextMap(const char* mapFile);

	void SpawnPlayer(Player* player, int startX, int startY);
private:
	void DrawTile(int tx, int ty, Surface* screen, int x, int y);

private:
	int m_mapWidth, m_mapHeight;

	Surface* m_tiles;
	std::vector<std::vector<char>> m_tileMap;
};