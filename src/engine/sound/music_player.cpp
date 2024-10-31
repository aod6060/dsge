#include "SDL_mixer.h"
#include "sound_hidden.h"
#include <iomanip>
#include <sstream>


namespace sound {
        void MusicPlayer::init(std::string name) {
            this->name = name;
        }

        void MusicPlayer::release() {
            // Not real sure what to put here
        }

        /*
            numLoops = -1 plays infinately until stopped
            numLoops = n >= 0 plays a number of times if 0 places once, if 1 plays twice, etc.
        */ 
        void MusicPlayer::play(int numLoops) {
            Mix_PlayMusic(sound::getMusicStream(this->name), numLoops);
        }

        void MusicPlayer::stop() {
            Mix_HaltMusic();
        }

        void MusicPlayer::resume() {
            Mix_ResumeMusic();
        }

        void MusicPlayer::pause() {
            Mix_PauseMusic();
        }

        bool MusicPlayer::isPlaying() {
            return Mix_PlayingMusic() ? true : false;
        }

        bool MusicPlayer::isPaused() {
            return Mix_PausedMusic() ? true : false;
        }

        void MusicPlayer::rewind() {
            Mix_RewindMusic();
        }

        // This is 
        void MusicPlayer::setPosition(double position) {
            Mix_SetMusicPosition(position);
        }

        double MusicPlayer::getPosition() {
            return Mix_GetMusicPosition(sound::getMusicStream(this->name));
        }

        double MusicPlayer::getMusicDuration() {
            return Mix_MusicDuration(sound::getMusicStream(this->name));
        }

        void MusicPlayer::setName(std::string name) {
            this->name = name;
        }

        std::string MusicPlayer::getName() {
            return this->name;
        }

        std::string MusicPlayer::toMaxTimeString() {
            double maxTime = this->getMusicDuration();

            int maxTimeInt = (int)maxTime;


            int minute = maxTimeInt / 60;
            int second = maxTimeInt % 60;

            std::stringstream ss;
            ss << minute << ":" << std::setw(2) << std::setfill('0') << second;

            return ss.str();
        }

        std::string MusicPlayer::toCurrentPositionString() {
            double maxTime = this->getPosition();

            int maxTimeInt = (int)maxTime;


            int minute = maxTimeInt / 60;
            int second = maxTimeInt % 60;

            std::stringstream ss;
            ss << minute << ":" << std::setw(2) << std::setfill('0') << second;

            return ss.str();
        }
}