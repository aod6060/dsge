#ifndef LW_INTERNAL_H
#define LW_INTERNAL_H



#include "../sys.h"
#include "lua.h"
#include "lw.h"

namespace lua_wrapper {

    void initLibs(LWState* state);

    // Export
    /*
    void export_initLibs(LWState* state);
    
    int lw_setInteger(lua_State* l);
    int lw_setNumber(lua_State* l);
    int lw_setBool(lua_State* l);

    int lw_getInteger(lua_State* l);
    int lw_getNumber(lua_State* l);
    int lw_getBool(lua_State* l);
    */

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

    // Render

    // Physics

    // Sound

    // igw
    
}

#endif