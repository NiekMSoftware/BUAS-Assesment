#pragma once

class ResourceHolder
{
public:
    // Disable copying
    ResourceHolder(const ResourceHolder&) = delete;
    ResourceHolder(ResourceHolder&&) = delete;
    void operator=(const ResourceHolder&) = delete;
    void operator=(ResourceHolder&&) = delete;

    // Retrieve instance
    static ResourceHolder& GetInstance();

    // holding on sprites
    void LoadSprite(const std::string& id, const char* fileName, int numFrames);
    Sprite* GetSprite(const std::string& id);
    Surface* GetSurface(const std::string& fileName);

    // holding on tilemaps
    void LoadTileMap(const std::string& id, const char* tilesetFile);
    TileMap* GetTileMap(const std::string& id);

private:
    ResourceHolder() { }
    ~ResourceHolder();

private:
    std::map<std::string, std::unique_ptr<Tmpl8::Sprite>> m_sprites; // stored sprites
    std::map<std::string, std::unique_ptr<Tmpl8::Surface>> m_surfaces; // stored surfaces
    std::map<std::string, std::unique_ptr<TileMap>> m_tileMaps;
};