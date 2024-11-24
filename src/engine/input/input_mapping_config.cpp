#include "input.h"
#include "input_happen.h"


namespace input {

    // Regular boolean check
    bool isInputMappingReleased(std::string name) {
        return input::isInputMappingReleased(&config::getConfig()->input.mapping[name].mapping);
    }

    bool isInputMappingPressedOnce(std::string name) {
        return input::isInputMappingPressedOnce(&config::getConfig()->input.mapping[name].mapping);
    }

    bool isInputMappingPressed(std::string name) {
        return input::isInputMappingPressed(&config::getConfig()->input.mapping[name].mapping);
    }

    bool isInputMappingReleasedOnce(std::string name) {
        return input::isInputMappingReleasedOnce(&config::getConfig()->input.mapping[name].mapping);
    }

    // Axis Functions
    float getInputMappingAxisReleased(std::string negative, std::string positive) {
        return 
            input::getInputMappingAxisReleased(
                &config::getConfig()->input.mapping[negative].mapping,
                &config::getConfig()->input.mapping[positive].mapping
            );
    }

    float getInputMappingAxisPressedOnce(std::string negative, std::string positive) {
        return 
            input::getInputMappingAxisPressedOnce(
                &config::getConfig()->input.mapping[negative].mapping,
                &config::getConfig()->input.mapping[positive].mapping
            );
    }

    float getInputMappingAxisPressed(std::string negative, std::string positive) {
        return 
            input::getInputMappingAxisPressed(
                &config::getConfig()->input.mapping[negative].mapping,
                &config::getConfig()->input.mapping[positive].mapping
            );
    }

    float getInputMappingAxisReleasedOnce(std::string negative, std::string positive) {
        return 
            input::getInputMappingAxisReleasedOnce(
                &config::getConfig()->input.mapping[negative].mapping,
                &config::getConfig()->input.mapping[positive].mapping
            );
    }

    // Value Functions
    float getInputMappingValueReleased(std::string name) {
        return input::getInputMappingValueReleased(&config::getConfig()->input.mapping[name].mapping);
    }

    float getInputMappingValuePressedOnce(std::string name) {
        return input::getInputMappingValuePressedOnce(&config::getConfig()->input.mapping[name].mapping);
    }

    float getInputMappingValuePressed(std::string name) {
        return input::getInputMappingValuePressed(&config::getConfig()->input.mapping[name].mapping);
    }

    float getInputMappingValueReleasedOnce(std::string name) {
        return input::getInputMappingValueReleasedOnce(&config::getConfig()->input.mapping[name].mapping);
    }

}