#include "SDL_events.h"
#include "SDL_gamecontroller.h"
#include "SDL_joystick.h"
#include "input.h"
#include "input_happen.h"
#include <algorithm>


namespace input {
    namespace gamepad {
        static int32_t DEAD_ZONE = 16000;

        static PlayerControllerData playerData[PlayerControllerName::PCN_PLAYER_MAX_SIZE];

        SDL_GameController* findController() {
            for(int i = 0; i < SDL_NumJoysticks(); i++) {
                if(SDL_IsGameController(i)) {
                    return SDL_GameControllerOpen(i);
                }
            }
            return nullptr;
        }

        void init() {
            for(int i = 0; i < PlayerControllerName::PCN_PLAYER_MAX_SIZE; i++) {
                playerData[i].leftAxis = glm::vec2(0.0f);
                playerData[i].rightAxis = glm::vec2(0.0f);
                playerData[i].leftTrigger = 0.0f;
                playerData[i].rightTrigger = 0.0f;
                playerData[i].name = (PlayerControllerName)(i);
                playerData[i].cButtons.resize(ControllerButton::CB_MAX_SIZE);

                for(int j = 0; j < playerData[i].cButtons.size(); j++) {
                    playerData[i].cButtons[j] = input::InputState::IS_RELEASED;
                }
            }

            std::cout << "Hello, World" << "\n";
        }

        void release() {
            for(int i =0; i < PlayerControllerName::PCN_PLAYER_MAX_SIZE; i++) {
                if(playerData[i].controller) {
                    SDL_GameControllerClose(playerData[i].controller);
                }
            }
        }

        void handleEvent(SDL_Event* e) {
            switch(e->type) {
                case SDL_CONTROLLERDEVICEADDED:
                    {
                        int32_t index = e->cdevice.which;
                        if(!playerData[index].controller) {
                            playerData[index].controller = SDL_GameControllerOpen(index);
                            playerData[index].gamePadType = (SDL_GameControllerType)(e->cdevice.type);

                            if (playerData[index].gamePadType == SDL_GameControllerType::SDL_CONTROLLER_TYPE_PS4) {
                                std::cout << index << "> Is a PS4 Controller\n";
                            }
                            else if (playerData[index].gamePadType == SDL_GameControllerType::SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO) {
                                std::cout << index << "> Is a nintendo pro Controller\n";
                            }

                        }
                    }
                    break;
                case SDL_CONTROLLERDEVICEREMOVED:
                    {
                        int32_t index = e->cdevice.which;
                        if(playerData[index].controller && e->cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(playerData[index].controller))) {
                            SDL_GameControllerClose(playerData[index].controller);
                        }
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    {
                        int32_t index = e->cbutton.which;
                        if(playerData[index].controller && e->cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(playerData[index].controller))) {
                            if(playerData[index].cButtons[e->cbutton.button] == input::InputState::IS_RELEASED) {
                                playerData[index].cButtons[e->cbutton.button] = input::InputState::IS_PRESSED_ONCE;
                            }
                        }
                    }
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    {
                        int32_t index = e->cbutton.which;
                        if(playerData[index].controller && e->cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(playerData[index].controller))) {
                            if(playerData[index].cButtons[e->cbutton.button] == input::InputState::IS_PRESSED) {
                                playerData[index].cButtons[e->cbutton.button] = input::InputState::IS_RELEASED_ONCE;
                            }
                        }
                    }
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    {
                       int32_t index = e->caxis.which;
                        if(playerData[index].controller && e->cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(playerData[index].controller))) {
                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                                if(e->caxis.value > DEAD_ZONE) {
                                    playerData[index].leftAxis.x = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                                } else if(e->caxis.value < -DEAD_ZONE) {
                                    playerData[index].leftAxis.x = -(e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MIN));
                                } else {
                                    playerData[index].leftAxis.x = 0.0f;
                                }
                            }

                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                                if(e->caxis.value > DEAD_ZONE) {
                                    playerData[index].leftAxis.y = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                                } else if(e->caxis.value < -DEAD_ZONE) {
                                    playerData[index].leftAxis.y = -(e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MIN));
                                } else {
                                    playerData[index].leftAxis.y = 0.0f;
                                }    
                            }

                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
                               if(e->caxis.value > DEAD_ZONE) {
                                    playerData[index].rightAxis.x = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                                } else if(e->caxis.value < -DEAD_ZONE) {
                                    playerData[index].rightAxis.x = -(e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MIN));
                                } else {
                                    playerData[index].rightAxis.x = 0.0f;
                                }
                            }

                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
                                if(e->caxis.value > DEAD_ZONE) {
                                    playerData[index].rightAxis.y = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                                } else if(e->caxis.value < -DEAD_ZONE) {
                                    playerData[index].rightAxis.y = -(e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MIN));
                                } else {
                                    playerData[index].rightAxis.y = 0.0f;
                                }
                            }

                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
                                playerData[index].leftTrigger = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                            }

                            if(e->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
                                playerData[index].rightTrigger = e->caxis.value / (float)(SDL_JOYSTICK_AXIS_MAX);
                            }

                        }
                    }
                    break;
                default:
                    break;
            }
        }

        void update() {
            std::function<void(InputState&)> updateState = [](InputState& state) {
                if(state == InputState::IS_PRESSED_ONCE) {
                    state = InputState::IS_PRESSED;
                }

                if(state == InputState::IS_RELEASED_ONCE) {
                    state = InputState::IS_RELEASED;
                }
            };

            for(int i = 0; i < PlayerControllerName::PCN_PLAYER_MAX_SIZE; i++) {
                if(playerData[i].controller) {
                    std::for_each(playerData[i].cButtons.begin(), playerData[i].cButtons.end(), updateState);
                }
            }
        }

        glm::vec2 getLeftAxis(PlayerControllerName name) {
            return playerData[name].leftAxis;
        }

        glm::vec2 getRightAxis(PlayerControllerName name) {
            return playerData[name].rightAxis;
        }

        float getLeftTriggerAxis(PlayerControllerName name) {
            return playerData[name].leftTrigger;
        }

        float getRightTriggerAxis(PlayerControllerName name) {
            return playerData[name].rightTrigger;
        }

        bool isButtonReleased(PlayerControllerName name, ControllerButton button) {
            return playerData[name].cButtons[button] == input::InputState::IS_RELEASED || playerData[name].cButtons[button] == input::InputState::IS_RELEASED_ONCE;
        }

        bool isButtonPressedOnce(PlayerControllerName name, ControllerButton button) {
            return playerData[name].cButtons[button] == input::InputState::IS_PRESSED_ONCE;
        }

        bool isButtonPressed(PlayerControllerName name, ControllerButton button) {
            return playerData[name].cButtons[button] == input::InputState::IS_PRESSED || playerData[name].cButtons[button] == input::InputState::IS_PRESSED_ONCE;
        }

        bool isButtonReleasedOnce(PlayerControllerName name, ControllerButton button) {
            return playerData[name].cButtons[button] == input::InputState::IS_RELEASED_ONCE;
        }

        bool isControllerConnected(PlayerControllerName name) {
            return playerData[name].controller;
        }
    }
}