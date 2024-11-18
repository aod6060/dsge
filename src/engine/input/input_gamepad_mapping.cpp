#include "input.h"
#include "input_happen.h"


namespace input {
    namespace gamepad {

        void initInputMapping(InputMapping* mapping, PlayerControllerName name, ControllerButton button) {
            mapping->name = name;
            mapping->button = button;
        }

        // Regular boolean check
        bool isInputMappingReleased(InputMapping* mapping) {
            return isButtonReleased(mapping->name, mapping->button);
        }

        bool isInputMappingPressedOnce(InputMapping* mapping) {
            return isButtonPressedOnce(mapping->name, mapping->button);
        }

        bool isInputMappingPressed(InputMapping* mapping) {
            return isButtonPressed(mapping->name, mapping->button);
        }

        bool isInputMappingReleasedOnce(InputMapping* mapping) {
            return isButtonReleasedOnce(mapping->name, mapping->button);
        }

        // Axis Functions
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
}