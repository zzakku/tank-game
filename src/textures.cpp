#include "textures.h"

namespace textures
{
    std::unordered_map<std::string, Texture2D> texture_map;

    void InitTextures()
    {
        texture_map["player"] = LoadTexture("res/player.png");
        texture_map["blocks"] = LoadTexture("res/tileset.png");
        texture_map["projectile"] = LoadTexture("res/projectile.png");
        texture_map["explosion"] = LoadTexture("res/explosion.png");
        texture_map["logo"] = LoadTexture("res/logo.png");
        texture_map["border"] = LoadTexture("res/border.png");
    }

    void UnloadTextures()
    {
        UnloadTexture(texture_map["player"]);
        UnloadTexture(texture_map["tileset"]);
        UnloadTexture(texture_map["projectile"]);
        UnloadTexture(texture_map["explosion"]);
    }

    Texture2D GetTexture(const std::string& key)
    {
        return texture_map[key];
    }
}