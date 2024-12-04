#ifndef LW_INTERNAL_H
#define LW_INTERNAL_H



#include "../sys.h"

namespace lua_wrapper {

    void initLibs(LWState* state);

    // Export
    int lw_export(lua_State* l);
    
    // Config


    // App

    void lw_app_initLib(LWState* state);

    int lw_app_getWidth(lua_State* l);
    int lw_app_getHeight(lua_State* l);
    int lw_app_getAspect(lua_State* l);

    int lw_app_exit(lua_State* l);

    int lw_app_getWindow(lua_State* l);
    int lw_app_getContext(lua_State* l);

    // Input
    void lw_input_initLib(LWState* state);

    int lw_input_isKeyReleased(lua_State* l);
    int lw_input_isKeyPressedOnce(lua_State* l);
    int lw_input_isKeyPressed(lua_State* l);
    int lw_input_isKeyReleasedOnce(lua_State* l);

    int lw_input_isMouseButtonReleased(lua_State* l);
    int lw_input_isMouseButtonPressedOnce(lua_State* l);
    int lw_input_isMouseButtonPressed(lua_State* l);
    int lw_input_isMouseButtonReleasedOnce(lua_State* l);

    int lw_input_getPosition(lua_State* l);
    int lw_input_getRelative(lua_State* l);
    
    int lw_input_getMouseWheel(lua_State* l);
    
    int lw_input_setGrab(lua_State* l);
    int lw_input_getGrab(lua_State* l);
    int lw_input_toggleGrab(lua_State* l);

    // Regular boolean check
    //bool isInputMappingReleased(std::string name);
    int lw_input_isInputMappingReleased(lua_State* l);

    //bool isInputMappingPressedOnce(std::string name);
    int lw_input_isInputMappingPressedOnce(lua_State* l);

    //bool isInputMappingPressed(std::string name);
    int lw_input_isInputMappingPressed(lua_State* l);

    //bool isInputMappingReleasedOnce(std::string name);
    int lw_input_isInputMappingReleasedOnce(lua_State* l);

    // Axis Functions
    //float getInputMappingAxisReleased(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisReleased(lua_State* l);

    //float getInputMappingAxisPressedOnce(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisPressedOnce(lua_State* l);

    //float getInputMappingAxisPressed(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisPressed(lua_State* l);

    //float getInputMappingAxisReleasedOnce(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisReleasedOnce(lua_State* l);


    // Value Functions
    //float getInputMappingValueReleased(std::string name);
    int lw_input_getInputMappingValueReleased(lua_State* l);

    //float getInputMappingValuePressedOnce(std::string name);
    int lw_input_getInputMappingValuePressedOnce(lua_State* l);

    //float getInputMappingValuePressed(std::string name);
    int lw_input_getInputMappingValuePressed(lua_State* l);

    //float getInputMappingValueReleasedOnce(std::string name);
    int lw_input_getInputMappingValueReleasedOnce(lua_State* l);

    // Gamepad Section
    void lw_gamepad_initLib(LWState* state);

    // glm::vec2 getLeftAxis(PlayerControllerName name);
    int lw_gamepad_player1_getLeftAxis(lua_State* l);
    int lw_gamepad_player2_getLeftAxis(lua_State* l);
    int lw_gamepad_player3_getLeftAxis(lua_State* l);
    int lw_gamepad_player4_getLeftAxis(lua_State* l);

    // glm::vec2 getRightAxis(PlayerControllerName name);
    int lw_gamepad_player1_getRightAxis(lua_State* l);
    int lw_gamepad_player2_getRightAxis(lua_State* l);
    int lw_gamepad_player3_getRightAxis(lua_State* l);
    int lw_gamepad_player4_getRightAxis(lua_State* l);

    // float getLeftTriggerAxis(PlayerControllerName name);
    int lw_gamepad_player1_getLeftTriggerAxis(lua_State* l);
    int lw_gamepad_player2_getLeftTriggerAxis(lua_State* l);
    int lw_gamepad_player3_getLeftTriggerAxis(lua_State* l);
    int lw_gamepad_player4_getLeftTriggerAxis(lua_State* l);

    // float getRightTriggerAxis(PlayerControllerName name);
    int lw_gamepad_player1_getRightTriggerAxis(lua_State* l);
    int lw_gamepad_player2_getRightTriggerAxis(lua_State* l);
    int lw_gamepad_player3_getRightTriggerAxis(lua_State* l);
    int lw_gamepad_player4_getRightTriggerAxis(lua_State* l);

    // bool isButtonReleased(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonReleased(lua_State* l);
    int lw_gamepad_player2_isButtonReleased(lua_State* l);
    int lw_gamepad_player3_isButtonReleased(lua_State* l);
    int lw_gamepad_player4_isButtonReleased(lua_State* l);

    // bool isButtonPressedOnce(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonPressedOnce(lua_State* l);
    int lw_gamepad_player2_isButtonPressedOnce(lua_State* l);
    int lw_gamepad_player3_isButtonPressedOnce(lua_State* l);
    int lw_gamepad_player4_isButtonPressedOnce(lua_State* l);

    // bool isButtonPressed(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonPressed(lua_State* l);
    int lw_gamepad_player2_isButtonPressed(lua_State* l);
    int lw_gamepad_player3_isButtonPressed(lua_State* l);
    int lw_gamepad_player4_isButtonPressed(lua_State* l);

    // bool isButtonReleasedOnce(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonReleasedOnce(lua_State* l);
    int lw_gamepad_player2_isButtonReleasedOnce(lua_State* l);
    int lw_gamepad_player3_isButtonReleasedOnce(lua_State* l);
    int lw_gamepad_player4_isButtonReleasedOnce(lua_State* l);


    // bool isControllerConnected(PlayerControllerName name);
    int lw_gamepad_player1_isControllerConnect(lua_State* l);
    int lw_gamepad_player2_isControllerConnect(lua_State* l);
    int lw_gamepad_player3_isControllerConnect(lua_State* l);
    int lw_gamepad_player4_isControllerConnect(lua_State* l);

    // Regular boolean check
    //bool isInputMappingReleased(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingReleased(lua_State* l);
    int lw_gamepad_player2_isInputMappingReleased(lua_State* l);
    int lw_gamepad_player3_isInputMappingReleased(lua_State* l);
    int lw_gamepad_player4_isInputMappingReleased(lua_State* l);

    //bool isInputMappingPressedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingPressedOnce(lua_State* l);
    int lw_gamepad_player2_isInputMappingPressedOnce(lua_State* l);
    int lw_gamepad_player3_isInputMappingPressedOnce(lua_State* l);
    int lw_gamepad_player4_isInputMappingPressedOnce(lua_State* l);

    //bool isInputMappingPressed(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingPressed(lua_State* l);
    int lw_gamepad_player2_isInputMappingPressed(lua_State* l);
    int lw_gamepad_player3_isInputMappingPressed(lua_State* l);
    int lw_gamepad_player4_isInputMappingPressed(lua_State* l);

    //bool isInputMappingReleasedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingReleasedOnce(lua_State* l);
    int lw_gamepad_player2_isInputMappingReleasedOnce(lua_State* l);
    int lw_gamepad_player3_isInputMappingReleasedOnce(lua_State* l);
    int lw_gamepad_player4_isInputMappingReleasedOnce(lua_State* l);

    // Axis Functions
    //float getInputMappingAxisReleased(PlayerControllerName name, std::string negative, std::string positive);
    //float getInputMappingAxisPressedOnce(PlayerControllerName name, std::string negative, std::string positive);
    //float getInputMappingAxisPressed(PlayerControllerName name, std::string negative, std::string positive);
    //float getInputMappingAxisReleasedOnce(PlayerControllerName name, std::string negative, std::string positive);

    // Value Functions
    //float getInputMappingValueReleased(PlayerControllerName name, std::string mapping);
    //float getInputMappingValuePressedOnce(PlayerControllerName name, std::string mapping);
    //float getInputMappingValuePressed(PlayerControllerName name, std::string mapping);
    //float getInputMappingValueReleasedOnce(PlayerControllerName name, std::string mapping);

    // Render

    // Physics

    // Sound

    // igw
    
}

#endif