#pragma once

#define TILESIZE 32
#define PADDING 1

class TileMap
{
public:
	TileMap(const char* fileName);
	~TileMap();

	void DrawMap(Surface* screen);
	void DrawTile(int tx, int ty, Surface* screen, int x, int y);

	void LoadMap(const char* mapFile);
private:
	int m_mapWidth, m_mapHeight;

	Surface* m_tiles;
	std::vector<std::vector<char>> m_tileMap;
};