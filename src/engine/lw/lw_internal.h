#ifndef LW_INTERNAL_H
#define LW_INTERNAL_H



#include "../sys.h"

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

    // Input

    // Render

    // Physics

    // Sound

    // igw
    
}

#endif