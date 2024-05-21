#include "font.h"
#include <unordered_map>

namespace fonts
{
    std::unordered_map<std::string, Font> font_map;

    void InitFonts()
    {
        font_map["gametext"] = LoadFont("res/PublicPixel.ttf");
    }

    void UnloadFonts()
    {
        UnloadFont(font_map["gametext"]);
    }

    Font GetFont(const std::string& key)
    {
        return font_map[key];
    }
}