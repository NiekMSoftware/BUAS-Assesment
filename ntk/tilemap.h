#pragma once

#define TILESIZE 32
#define PADDING 1

class TileMap
{
public:
	TileMap(const char* fileName, int mapWidth, int mapHeight);
	~TileMap();

	void DrawMap(int mapWidth, int mapHeight, Surface* screen);
	void DrawTile(int tx, int ty, Surface* screen, int x, int y);
private:
	int m_mapWidth, m_mapHeight;

	Surface* m_tiles;
};