#ifndef SRC_TANK_FONT_H
#define SRC_TANK_FONT_H

#include <raylib.h>
#include <string>

namespace fonts
{
    void InitFonts();
    void UnloadFonts();
    Font GetFont(const std::string& key);
}

#endif // SRC_TANK_FONT_H