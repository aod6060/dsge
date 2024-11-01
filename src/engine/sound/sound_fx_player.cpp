#include "SDL_mixer.h"
#include "sound_hidden.h"


namespace sound {
    void SoundFXPlayer::init(std::string name) {
        this->name = name;
    }

    void SoundFXPlayer::release() {
        // Not real sure what to do here
    }

    void SoundFXPlayer::play(int channel, int loop, bool is2D) {
        this->channel = Mix_PlayChannel(channel, sound::getSoundFXStream(this->name), loop);
        Mix_SetPosition(this->channel, 0, 0);
        this->is2D = is2D;
    }

    void SoundFXPlayer::stop() {
        Mix_HaltChannel(this->channel);
    }

    void SoundFXPlayer::resume() {
        Mix_Resume(this->channel);
    }

    void SoundFXPlayer::pause() {
        Mix_Pause(this->channel);
    }

    bool SoundFXPlayer::isPlaying() {
        return Mix_Playing(this->channel);
    }

    bool SoundFXPlayer::isPaused() {
        return Mix_Paused(this->channel);
    }

    void SoundFXPlayer::setName(std::string name) {
        this->name = name;
    }

    std::string SoundFXPlayer::getName() {
        return name;
    }

    void SoundFXPlayer::setPosition(const glm::vec2& position) {
        this->postion = position;
    }

    void SoundFXPlayer::setScaledDistance(float scaledDistance) {
        this->scaledDistance = scaledDistance;
    }

    void SoundFXPlayer::update() {

        if(this->is2D) {
            // Get Direction
            glm::vec2 direction = sound::getListenerPosition() - this->postion;
            // Get Distance
            float distance = glm::abs(glm::length(direction));
            distance = glm::clamp(distance, 0.0f, this->scaledDistance);

            // Get Actual Distance
            float actualDistance = glm::mix(0.0f, 255.0f, distance / this->scaledDistance);
            float distVolume = glm::mix(0.0f, (float)MIX_MAX_VOLUME, distance / this->scaledDistance);

            
            std::cout << distVolume << "\n";

            // Get the Angle
            glm::vec2 nd = glm::normalize(direction);
            float angle = glm::degrees(atan2(-nd.x, nd.y));


            // Call the Mix_SetPosition function
            Mix_SetPosition(this->channel, (int16_t)(angle), (uint8_t)(actualDistance));
            //Mix_Volume(this->channel, MIX_MAX_VOLUME - (int)(distVolume));
        } else {
            Mix_SetPosition(this->channel, 0, 0);
        }
    }
}