#ifndef CONFIG_H
#define CONFIG_H


#include <string>
#include <map>
#include <vector>
#include "../input/input.h"

namespace config {
    struct Application {
        std::string caption;
        bool fullscreen;
        uint32_t display;
        uint32_t resolution;
    };

    struct GamepadInputMapping {
        std::string name;
        std::string currentButton = "CB_INVALID";
        input::gamepad::InputMapping mapping;
    };

    struct Player {
        input::gamepad::PlayerControllerName name;
        std::map<std::string, GamepadInputMapping> mapping;
    };

    struct Gamepad {
        //std::map<std::string, input::gamepad::InputMapping> mapping;
        std::vector<Player> players; // This will
    };

    struct KeyboardMouseInputMap {
        std::string name;
        std::string currentMouseButton = "MBS_LEFT";
        std::string currentKey = "KEYS_UNKNOWN";
        input::InputMapping mapping;
    };

    struct Input {
        std::map<std::string, KeyboardMouseInputMap> mapping;
        Gamepad gamepad;
    };
    
    struct Render {};
    
    struct Physics {};

    struct Sound {
        float masterVolume;
        float musicVolume;
        float soundFXVolume;
    };

    struct Config {
        Application application;
        Input input;
        Render render;
        Physics physics;
        Sound sound;
    };

    void init();
    void release();

    Config* getConfig();

    void reload();

    void getKeysList(std::vector<std::string>& keyList);
    void getMouseButtonList(std::vector<std::string>& list);
    void getPlayerNameList(std::vector<std::string>& list);
    void getGamePadButtonList(std::vector<std::string>& list);
     
    void save();

    bool drawConfigSystem();

}

#endif