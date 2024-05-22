#include "sound.h"
#include <unordered_map>

namespace sounds
{
    std::unordered_map<std::string, Sound> soundeffects;
    std::unordered_map<std::string, Music> music;

    void InitSounds()
    {
//        InitAudioDevice();

        soundeffects["explosion"] = LoadSound("res/soundtracks/Explosion.wav");
        soundeffects["bullet"] = LoadSound("res/soundtracks/Gun.wav");



        music["electrophilia"] = LoadMusicStream("res/soundtracks/psiriuselectrophilia.xm");
        music["electrophilia"].looping = true;
//        SetMusicVolume(music["electrophilia"], 0.25f);
        
    }

    void UnloadSounds()
    {
        if (IsMusicStreamPlaying(music["alpha"]))
        {
            StopBGM("alpha");
        }

        CloseAudioDevice();

        UnloadSound(soundeffects["explosion"]);
        UnloadSound(soundeffects["bullet"]);
    }

    void PlaySFX(const std::string& key)
    {
        if (soundeffects.find(key) == soundeffects.end())
        {
            return;
        }
        else
        {
            PlaySound(soundeffects[key]);
        }
    }

    void UpdateBGM(const std::string& key)
    {
        if (music.find(key) == music.end())
        {
            return;
        }
        else
        {
		if (IsMusicStreamPlaying(music[key]))
			UpdateMusicStream(music[key]);
        }
    }

    void StartBGM(const std::string& key)
    {
        if (music.find(key) == music.end())
        {
            return;
        }
        else
        {
		if (!IsMusicStreamPlaying(music[key]))
			PlayMusicStream(music[key]);
        }

    }

    void StopBGM(const std::string& key)
    {
        if (music.find(key) == music.end())
        {
            return;
        }
        else
        {
		if (IsMusicStreamPlaying(music[key]))
			StopMusicStream(music[key]);
        }        
    }
}