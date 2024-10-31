#include "SDL_mixer.h"
#include "sound_hidden.h"
#include <map>


namespace sound {

    // MusicStream
    std::map<std::string, Mix_Music*> musicStream;
    // SoundFX
    std::map<std::string, Mix_Chunk*> soundFXStream;

    // This section is for normal soundfx

    // Positional SoundFX
    glm::vec2 listener_pos = glm::vec2(0.0f);

    void init() {
        // TODO: Figure out how Mix_Init and Mix_Quit works and if I need it.
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    }

    void release() {
        // TODO: Figure out how Mix_Init and Mix_Quit works and if I need it.

        // Releawse musicStreams
        for(std::map<std::string, Mix_Music*>::iterator it = musicStream.begin(); it != musicStream.end(); it++) {
            Mix_FreeMusic(it->second);
        }
        musicStream.clear();

        // Release soundFXStreams
        for(std::map<std::string, Mix_Chunk*>::iterator it = soundFXStream.begin(); it != soundFXStream.end(); it++) {
            Mix_FreeChunk(it->second);
        }
        soundFXStream.clear();

        Mix_CloseAudio();
        Mix_Quit();
    }

    void addMusicStream(std::string name, std::string path) {
        musicStream[name] = Mix_LoadMUS(path.c_str());
    }

    void addSoundFXStream(std::string name, std::string path) {
        soundFXStream[name] = Mix_LoadWAV(path.c_str());
    }

    Mix_Music* getMusicStream(std::string name) {
        return musicStream.at(name);
    }
    
    Mix_Chunk* getSoundFXStream(std::string name) {
        return soundFXStream.at(name);
    }

    void getMusicStreamNames(std::vector<std::string>& names) {
        for(std::map<std::string, Mix_Music*>::iterator it = musicStream.begin(); it != musicStream.end(); it++) {
            names.push_back(it->first);
        }
    }

    void getSoundFXStreamNames(std::vector<std::string>& names) {
        for(std::map<std::string, Mix_Chunk*>::iterator it = soundFXStream.begin(); it != soundFXStream.end(); it++) {
            names.push_back(it->first);
        }
    }

    void setListenerPosition(const glm::vec2& pos) {
        listener_pos = pos;
    }

    glm::vec2 getListenerPosition() {
        return listener_pos;
    }
    
    void setMasterVolume(float volume) {
        int v = (int)(volume * MIX_MAX_VOLUME);
        Mix_MasterVolume(v);
    }
    
    void setMusicVolume(float volume) {
        int v = (int)(volume * MIX_MAX_VOLUME);
        Mix_VolumeMusic(v);
    }
    
    void setSoundFXVolume(float volume) {
        int v = (int)(volume * MIX_MAX_VOLUME);
        Mix_Volume(-1, v);
    }
}