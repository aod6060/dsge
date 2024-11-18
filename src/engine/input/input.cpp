#include "input.h"
#include "../sys.h"

namespace input {

    // Keyboard Attributes
    std::vector<InputState> keys;

    // Mouse Attributes
    std::vector<InputState> mouseButtons;
    glm::vec2 position;
    glm::vec2 relative;
    glm::vec2 wheel;

    float time = 0.0;
    float maxTime = 1.0;


    void init() {
        // Keyboard
        keys.resize(Keyboard::KEYS_MAX_SIZE);

        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            state = InputState::IS_RELEASED;
        });

        // Mouse Buttons
        mouseButtons.resize(MouseButtons::MBS_MAX_SIZE);

        std::for_each(mouseButtons.begin(), mouseButtons.end(), [](InputState& state) {
            state = InputState::IS_RELEASED;
        });

        // Mouse Position
        position = glm::vec2(0.0f, 0.0f);

        // Mouse Relative
        relative = glm::vec2(0.0f, 0.0f);

        // Mouse Wheel
        wheel = glm::vec2(0.0f, 0.0f);

        gamepad::init();
    }

    void handleEvent(SDL_Event* e) {
        if(e->type == SDL_KEYDOWN) {
            if(keys[e->key.keysym.scancode] == InputState::IS_RELEASED) {
                keys[e->key.keysym.scancode] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_KEYUP) {
            if(keys[e->key.keysym.scancode] == InputState::IS_PRESSED) {
                keys[e->key.keysym.scancode] = InputState::IS_RELEASED_ONCE;
            }
        } else if(e->type == SDL_MOUSEBUTTONDOWN) {
            if(mouseButtons[e->button.button - 1] == InputState::IS_RELEASED) {
                mouseButtons[e->button.button - 1] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_MOUSEBUTTONUP) {
            if(mouseButtons[e->button.button - 1] == InputState::IS_PRESSED) {
                mouseButtons[e->button.button - 1] = InputState::IS_RELEASED_ONCE;
            }
        } else if(e->type == SDL_MOUSEMOTION) {
            position.x = e->motion.x;
            position.y = e->motion.y;
            relative.x = e->motion.xrel;
            relative.y = e->motion.yrel;
            time = 0.0f;
        } else if(e->type == SDL_MOUSEWHEEL) {
            wheel.x = e->wheel.x;
            wheel.y = e->wheel.y;
        }

        gamepad::handleEvent(e);
    }

    void update(float delta) {

        std::function<void(InputState&)> updateState = [](InputState& state) {
            if(state == InputState::IS_PRESSED_ONCE) {
                state = InputState::IS_PRESSED;
            }

            if(state == InputState::IS_RELEASED_ONCE) {
                state = InputState::IS_RELEASED;
            }
        };

        std::function<glm::vec2(glm::vec2, float t)> toZero = [](glm::vec2 a, float t) {
            glm::vec2 b = glm::vec2(0.0);
            return (b - a) * (t * t) + a;
        };

        // Keyboard
        std::for_each(keys.begin(), keys.end(),updateState);

        // Mouse Buttons
        std::for_each(mouseButtons.begin(), mouseButtons.end(), updateState);

        if(time < maxTime) {
            time += delta;
        }

        relative = toZero(relative, time * (1.0 / maxTime));

        wheel.x = 0.0f;
        wheel.y = 0.0f;

        gamepad::update();
    }

    void release() {
        gamepad::release();

        keys.clear();
        mouseButtons.clear();
    }

    // Keyboard
    bool isKeyReleased(const Keyboard& key) {
        return keys[key] == InputState::IS_RELEASED || keys[key] == InputState::IS_RELEASED_ONCE;
    }

    bool isKeyPressedOnce(const Keyboard& key) {
        return keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyPressed(const Keyboard& key) {
        return keys[key] == InputState::IS_PRESSED || keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyReleasedOnce(const Keyboard& key) {
        return keys[key] == InputState::IS_RELEASED_ONCE;
    }

    // Mouse
    bool isMouseButtonReleased(const MouseButtons& mb) {
        return mouseButtons[mb] == InputState::IS_RELEASED || mouseButtons[mb] == InputState::IS_RELEASED_ONCE;
    }

    bool isMouseButtonPressedOnce(const MouseButtons& mb) {
        return mouseButtons[mb] == InputState::IS_PRESSED_ONCE;
    }

    bool isMouseButtonPressed(const MouseButtons& mb) {
        return mouseButtons[mb] == InputState::IS_PRESSED || mouseButtons[mb] == InputState::IS_PRESSED_ONCE;
    }

    bool isMouseButtonReleasedOnce(const MouseButtons& mb) {
        return mouseButtons[mb] == InputState::IS_RELEASED_ONCE;
    }

    glm::vec2 getPosition() {
        return position;
    }

    glm::vec2 getRelative() {
        return relative;
    }

    glm::vec2 getMouseWheel() {
        return wheel;
    }

    void setGrab(bool grab) {
        SDL_SetRelativeMouseMode((grab) ? SDL_TRUE : SDL_FALSE);
    }

    bool getGrab() {
        return SDL_GetRelativeMouseMode() ? true : false;
    }

    void toggleGrab() {
        setGrab(!getGrab());
    }

}