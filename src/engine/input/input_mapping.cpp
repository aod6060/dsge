#include "input.h"
#include "input_happen.h"


namespace input {


    // Input Mapping
    void initInputMapping(InputMapping& mapping, int input, bool isMouse) {
        mapping.input = input;
        mapping.isMouse = isMouse;
    }

    bool isInputMappingReleased(InputMapping& mapping) {
        bool b = false;
        if(mapping.isMouse) {
            b = isMouseButtonReleased((MouseButtons)mapping.input);
        } else {
            b = isKeyReleased((Keyboard)mapping.input);
        }
        return b;
    }

    bool isInputMappingPressedOnce(InputMapping& mapping) {
        bool b = false;
        if(mapping.isMouse) {
            b = isMouseButtonPressedOnce((MouseButtons)mapping.input);
        } else {
            b = isKeyPressedOnce((Keyboard)mapping.input);
        }
        return b;
    }

    bool isInputMappingPressed(InputMapping& mapping) {
        bool b = false;
        if(mapping.isMouse) {
            b = isMouseButtonPressed((MouseButtons)mapping.input);
        } else {
            b = isKeyPressed((Keyboard)mapping.input);
        }
        return b;
    }

    bool isInputMappingReleasedOnce(InputMapping& mapping) {
        bool b = false;
        if(mapping.isMouse) {
            b = isMouseButtonReleasedOnce((MouseButtons)mapping.input);
        } else {
            b = isKeyReleasedOnce((Keyboard)mapping.input);
        }
        return b;
    }

    /*
        Basically this will 
    */
    float getInputMappingAxis(InputMapping& negative, InputMapping& positive) {
        float n = 0.0f;
        float p = 0.0f;

        if(isInputMappingPressed(negative)) {
            n = 1.0f;
        }

        if(isInputMappingPressed(positive)) {
            p = 1.0f;
        }

        return p - n;
    }
}