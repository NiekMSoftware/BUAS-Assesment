#pragma once

#define SPRITESIZE 32

class TileMap
{
public:
	TileMap(const char* tilesetPath, int mapWidth, int mapHeight, int frameCount);
	~TileMap();

	void DrawMap(Surface* screen, int offsetX, int offsetY);

	bool LoadMap(const std::string& filePath);
	bool CheckPos(int x, int y);

private:
	std::vector<std::vector<int>> m_map;
	std::vector<Sprite*> m_tileSprites;
	int m_width, m_height;
};