#include "input.h"
#include "input_happen.h"


namespace input {
    namespace gamepad {
    // Regular boolean check
        // Regular boolean check
        bool isInputMappingReleased(PlayerControllerName name, std::string mapping) {
            //isInputMappingReleased(&config::getConfig()->input.gamepad.players[name].mapping);
            return isInputMappingReleased(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        bool isInputMappingPressedOnce(PlayerControllerName name, std::string mapping) {
            return isInputMappingPressedOnce(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        bool isInputMappingPressed(PlayerControllerName name, std::string mapping) {
            return isInputMappingPressed(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        bool isInputMappingReleasedOnce(PlayerControllerName name, std::string mapping) {
            return isInputMappingReleasedOnce(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        // Axis Functions
        float getInputMappingAxisReleased(PlayerControllerName name, std::string negative, std::string positive) {
            return getInputMappingAxisReleased(
                &config::getConfig()->input.gamepad.players[name].mapping[negative].mapping,
                &config::getConfig()->input.gamepad.players[name].mapping[positive].mapping
            );
        }

        float getInputMappingAxisPressedOnce(PlayerControllerName name, std::string negative, std::string positive) {
            return getInputMappingAxisPressedOnce(
                &config::getConfig()->input.gamepad.players[name].mapping[negative].mapping,
                &config::getConfig()->input.gamepad.players[name].mapping[positive].mapping
            );
        }

        float getInputMappingAxisPressed(PlayerControllerName name, std::string negative, std::string positive) {
            return getInputMappingAxisPressed(
                &config::getConfig()->input.gamepad.players[name].mapping[negative].mapping,
                &config::getConfig()->input.gamepad.players[name].mapping[positive].mapping
            );           
        }

        float getInputMappingAxisReleasedOnce(PlayerControllerName name, std::string negative, std::string positive) {
            return getInputMappingAxisReleasedOnce(
                &config::getConfig()->input.gamepad.players[name].mapping[negative].mapping,
                &config::getConfig()->input.gamepad.players[name].mapping[positive].mapping
            );
        }

        // Value Functions
        float getInputMappingValueReleased(PlayerControllerName name, std::string mapping) {
            return getInputMappingValueReleased(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        float getInputMappingValuePressedOnce(PlayerControllerName name, std::string mapping) {
            return getInputMappingValuePressedOnce(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        float getInputMappingValuePressed(PlayerControllerName name, std::string mapping) {
            return getInputMappingValuePressed(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }

        float getInputMappingValueReleasedOnce(PlayerControllerName name, std::string mapping) {
            return getInputMappingValueReleasedOnce(&config::getConfig()->input.gamepad.players[name].mapping[mapping].mapping);
        }



    }
}