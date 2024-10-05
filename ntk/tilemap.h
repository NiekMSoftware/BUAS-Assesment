#pragma once

#define TILESIZE 32
#define PADDING 1

class TileMap
{
public:
	TileMap(const char* fileName, int mapWidth, int mapHeight, int tileSetWidth);
	~TileMap();

	void DrawMap(Surface* screen);
	void DrawTile(int tx, int ty, Surface* screen, int x, int y);

	void LoadMap(const char* mapFile);
	void ReadMap();
private:
	int m_mapWidth, m_mapHeight;
	int m_tilesetWidth;

	Surface* m_tiles;
	std::vector<std::vector<char>> m_tileMap;
};