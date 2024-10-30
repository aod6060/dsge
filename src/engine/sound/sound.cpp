#include "SDL_mixer.h"
#include "sound_hidden.h"
#include <map>


namespace sound {

    std::map<std::string, Music> music;
    std::string currentMusic = "";

    // This section is for normal soundfx

    // Positional SoundFX
    
    void init() {
        // TODO: Figure out how Mix_Init and Mix_Quit works and if I need it.
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);

        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    }

    void release() {
        // TODO: Figure out how Mix_Init and Mix_Quit works and if I need it.
        Mix_CloseAudio();
        Mix_Quit();
    }

    void addMusic(std::string name, std::string path, bool isLooping) {
        music[name].music = Mix_LoadMUS(path.c_str());
        music.at(name).isLooping = isLooping;
    }

    void addSoundFX(std::string name, std::string path) {

    }

    // Play Music
    void playMusic(std::string name) {
        Mix_PlayMusic(music.at(name).music, (music.at(name).isLooping) ? -1 : 0);
        currentMusic = name;
    }

    // Play SoundFX
    void playSoundFX(std::string name) {

    }

    // Play 2D Locational SoundFX
    void setListenerLocation(const glm::vec2& position) {

    }

    void setSoundFXLocation(std::string name, const glm::vec2& position) {

    }

    void playPositionalSoundFX(std::string name) {

    }

    // Setting for controlling sound will go here
    

}