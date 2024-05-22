#ifndef SRC_TANK_SOUND_H
#define SRC_TANK_SOUND_H

#include <raylib.h>
#include <string>

namespace sounds
{
    void InitSounds();
    
    void UnloadSounds();

    void PlaySFX(const std::string& key);

    void UpdateBGM(const std::string& key);

    void StartBGM(const std::string& key);

    void StopBGM(const std::string& key);
}

#endif // SRC_TANK_SOUND_H