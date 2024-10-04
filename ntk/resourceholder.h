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

    void LoadSprite(const std::string& id, const char* fileName, int numFrames);
    Tmpl8::Sprite* GetSprite(const std::string& id);
    Tmpl8::Surface* GetSurface(const std::string& fileName);

private:
    ResourceHolder() { }
    ~ResourceHolder();

private:
    std::map<std::string, std::unique_ptr<Tmpl8::Sprite>> m_sprites; // stored sprites
    std::map<std::string, std::unique_ptr<Tmpl8::Surface>> m_surfaces; // stored surfaces
};