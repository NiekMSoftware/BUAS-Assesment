// ResourceHolder Singleton

#include "precomp.h"
#include "resourceholder.h"

ResourceHolder::~ResourceHolder()
{
	m_sprites.clear();
	m_surfaces.clear();
}

ResourceHolder& ResourceHolder::GetInstance()
{
	static ResourceHolder instance;
	return instance;
}

void ResourceHolder::LoadSprite(const std::string& id, const char* fileName, int numFrames)
{
	// Check if surface is already loaded
	Surface* surface = GetSurface(fileName);
	if (!surface)
	{
		// Load the surface if it's not loaded
		std::unique_ptr<Surface> newSurface = std::make_unique<Surface>(fileName);
		surface = newSurface.get();
		m_surfaces.insert(std::make_pair(fileName, std::move(newSurface)));
	}

	// create sprite
	std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>(surface, numFrames);
	sprite->ownership = false;
	const auto inserted = m_sprites.insert(std::make_pair(id, std::move(sprite)));
	assert(inserted.second);
}

Tmpl8::Sprite* ResourceHolder::GetSprite(const std::string& id)
{
	// Find the sprite by ID
	auto it = m_sprites.find(id);
	if (it != m_sprites.end())
	{
		return it->second.get();
	}

	throw std::runtime_error("Sprite not found with id: " + id);
}

Tmpl8::Surface* ResourceHolder::GetSurface(const std::string& fileName)
{
	auto itr = m_surfaces.find(fileName);
	if (itr != m_surfaces.end()) return itr->second.get();
	return nullptr;
}

void ResourceHolder::LoadTileMap(const std::string& id, const char* tilesetFile)
{
	// check if the tile map is already loaded
	auto itr = m_tileMaps.find(id);
	if (itr == m_tileMaps.end())
	{
		std::unique_ptr<TileMap> newTileMap = std::make_unique<TileMap>(tilesetFile);
		const auto inserted = m_tileMaps.insert(std::make_pair(id, std::move(newTileMap)));
		assert(inserted.second);
	}
}

TileMap* ResourceHolder::GetTileMap(const std::string& id)
{
	auto itr = m_tileMaps.find(id);
	if (itr != m_tileMaps.end()) return itr->second.get();
	
	throw std::runtime_error("Tilemap not found with id: " + id);
}

