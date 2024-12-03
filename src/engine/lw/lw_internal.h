#ifndef LW_INTERNAL_H
#define LW_INTERNAL_H



#include "../sys.h"
#include "lua.h"
#include "lw.h"

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

    
    // Render

    // Physics

    // Sound

    // igw
    
}

#endif