#ifndef SOUND_H
#define SOUND_H


#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace sound {

    // Structs
    struct MusicPlayer {
        std::string name;

        void init(std::string name);
        void release();

        /*
            numLoops = -1 plays infinately until stopped
            numLoops = n >= 0 plays a number of times if 0 places once, if 1 plays twice, etc.
        */ 
        void play(int numLoops);

        void stop();

        void resume();

        void pause();

        bool isPlaying();

        bool isPaused();

        void rewind();

        // This is 
        void setPosition(double position);

        double getPosition();

    };

    struct SoundFXPlayer {
        std::string name;
    };

    struct SoundFXPlayer2D {
        std::string name;
        glm::vec2 postion;
        int channel;


    };

    // Functions
    void init();
    void release();

    void addMusicStream(std::string name, std::string path);
    void addSoundFXStream(std::string name, std::string path);

    void getMusicStreamNames(std::vector<std::string>& names);
    void getSoundFXStreamNames(std::vector<std::string>& names);

    void setListenerPosition(const glm::vec2& pos);

    void setMasterVolume(float volume);
    
    void setMusicVolume(float volume);
    
    void setSoundFXVolume(float volume);
}


#endif