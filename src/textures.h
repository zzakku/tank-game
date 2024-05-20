#ifndef SRC_TANK_TEXTURES_H
#define SRC_TANK_TEXTURES_H

#include <raylib.h>
#include <unordered_map>
#include <string>

// Это "менеджер текстур", хоть и не очень продвинутый. Просто глобальный map текстур, откуда сущности могут дёргать свой ID текстуры в GPU.

namespace textures
{
    void InitTextures();
    void UnloadTextures();
    Texture2D GetTexture(const std::string& key);
}

#endif // SRC_TANK_TEXTURES_H