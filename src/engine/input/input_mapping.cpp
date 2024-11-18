#include "input.h"
#include "input_happen.h"


namespace input {


    // Input Mapping
    void initInputMapping(InputMapping* mapping, int input, bool isMouse) {
        mapping->input = input;
        mapping->isMouse = isMouse;
    }

    bool isInputMappingReleased(InputMapping* mapping) {
        bool b = false;
        if(mapping->isMouse) {
            b = isMouseButtonReleased((MouseButtons)mapping->input);
        } else {
            b = isKeyReleased((Keyboard)mapping->input);
        }
        return b;
    }

    bool isInputMappingPressedOnce(InputMapping* mapping) {
        bool b = false;
        if(mapping->isMouse) {
            b = isMouseButtonPressedOnce((MouseButtons)mapping->input);
        } else {
            b = isKeyPressedOnce((Keyboard)mapping->input);
        }
        return b;
    }

    bool isInputMappingPressed(InputMapping* mapping) {
        bool b = false;
        if(mapping->isMouse) {
            b = isMouseButtonPressed((MouseButtons)mapping->input);
        } else {
            b = isKeyPressed((Keyboard)mapping->input);
        }
        return b;
    }

    bool isInputMappingReleasedOnce(InputMapping* mapping) {
        bool b = false;
        if(mapping->isMouse) {
            b = isMouseButtonReleasedOnce((MouseButtons)mapping->input);
        } else {
            b = isKeyReleasedOnce((Keyboard)mapping->input);
        }
        return b;
    }
    
    float getInputMappingAxisReleased(InputMapping* negative, InputMapping* positive) {
        return getInputMappingValueReleased(positive) - getInputMappingValueReleased(negative);
    }

    float getInputMappingAxisPressedOnce(InputMapping* negative, InputMapping* positive) {
        return getInputMappingValuePressedOnce(positive) - getInputMappingValuePressedOnce(negative);
    }

    float getInputMappingAxisPressed(InputMapping* negative, InputMapping* positive) {
        return getInputMappingValuePressed(positive) - getInputMappingValuePressed(negative);
    }

    float getInputMappingAxisReleasedOnce(InputMapping* negative, InputMapping* positive) {
        return getInputMappingValueReleasedOnce(positive) - getInputMappingValueReleasedOnce(negative);
    }

    // Value Functions
    float getInputMappingValueReleased(InputMapping* mapping) {
        return isInputMappingReleased(mapping) ? 1.0f : 0.0f;
    }

    float getInputMappingValuePressedOnce(InputMapping* mapping) {
        return isInputMappingPressedOnce(mapping) ? 1.0f : 0.0f;
    }

    float getInputMappingValuePressed(InputMapping* mapping) {
        return isInputMappingPressed(mapping) ? 1.0f : 0.0f;
    }

    float getInputMappingValueReleasedOnce(InputMapping* mapping) {
        return isInputMappingReleasedOnce(mapping) ? 1.0f : 0.0f;
    }

}