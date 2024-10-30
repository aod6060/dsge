#ifndef SOUND_H
#define SOUND_H


#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace sound {


    void init();
    void release();


    void addMusic(std::string name, std::string path, bool isLooping=true);
    void addSoundFX(std::string name, std::string path);


    // Play Music
    void playMusic(std::string name);


    // Play SoundFX
    void playSoundFX(std::string name);


    // Play 2D Locational SoundFX
    void setListenerLocation(const glm::vec2& position);
    void setSoundFXLocation(std::string name, const glm::vec2& position);
    void playPositionalSoundFX(std::string name);

    // Setting for controlling sound will go here

}


#endif