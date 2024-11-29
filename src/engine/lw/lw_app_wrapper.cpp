#include "lw_internal.h"
#include <functional>

namespace lua_wrapper {

    void lw_app_initLib(LWState* state) {
        // App.getWidth() or App.getHeight() etc

        lua_newtable(state->state); // -3

        std::function<void(lua_State*, std::string, lua_CFunction)> addToTable = [](lua_State* l, std::string name, lua_CFunction func){
            lua_pushstring(l, name.c_str());
            lua_pushcfunction(l, func);
            lua_settable(l, -3);
        };

        addToTable(state->state, "getWidth", lw_app_getWidth);
        addToTable(state->state, "getHeight", lw_app_getHeight);
        addToTable(state->state, "getAspect", lw_app_getAspect);
        addToTable(state->state, "exit", lw_app_exit);
        addToTable(state->state, "getWindow", lw_app_getWindow);
        addToTable(state->state, "getContext", lw_app_getContext);

        lua_setglobal(state->state, "App");
    }

    int lw_app_getWidth(lua_State* l) {
        lua_pushinteger(l, app::getWidth());
        return 1;
    }

    int lw_app_getHeight(lua_State* l) {
        lua_pushinteger(l, app::getHeight());
        return 1;
    }

    int lw_app_getAspect(lua_State* l) {
        lua_pushnumber(l, app::getAspect());
        return 1;
    }

    int lw_app_exit(lua_State* l) {
        app::exit();
        return 0;
    }

    int lw_app_getWindow(lua_State* l) {
        lua_pushlightuserdata(l, app::getWindow());
        return 1;
    }

    int lw_app_getContext(lua_State* l) {
        lua_pushlightuserdata(l, app::getContext());
        return 1;
    }

}