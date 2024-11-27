#include "lua.h"
#include "lw.h"
#include "lw_internal.h"

namespace lw {

    /*
    void export_initLibs(LuaState* state) {
        lua_newtable(state->state);
        
        lua_pushstring(state->state, "setInteger");
        lua_pushcfunction(state->state, lw_setInteger);
        lua_settable(state->state, -3);

        lua_pushstring(state->state, "setNumber");
        lua_pushcfunction(state->state, lw_setNumber);
        lua_settable(state->state, -3);

        lua_pushstring(state->state, "setBool");
        lua_pushcfunction(state->state, lw_setBool);
        lua_settable(state->state, -3);

        lua_pushstring(state->state, "getInteger");
        lua_pushcfunction(state->state, lw_getInteger);
        lua_settable(state->state, -3);

        lua_pushstring(state->state, "getNumber");
        lua_pushcfunction(state->state, lw_getNumber);
        lua_settable(state->state, -3);

        lua_pushstring(state->state, "getBool");
        lua_pushcfunction(state->state, lw_getBool);
        lua_settable(state->state, -3);

        lua_setglobal(state->state, "export");
    }

    int lw_setInteger(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        int32_t value = lua_tointeger(l, 3);
        s->exports.setInteger(name, value);
        return 0;
    }

    int lw_setNumber(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        float value = lua_tonumber(l, 3);
        s->exports.setNumber(name, value);
        return 0;
    }

    int lw_setBool(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        bool value = lua_toboolean(l, 3);
        s->exports.setBool(name, value);
        return 0;
    }

    int lw_getInteger(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        lua_pushinteger(l, s->exports.getInteger(name));
        return 1;
    }

    int lw_getNumber(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        lua_pushnumber(l, s->exports.getNumber(name));
        return 1;
    }

    int lw_getBool(lua_State* l) {
        LuaState* s = (LuaState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        lua_pushboolean(l, s->exports.getBool(name));
        return 1;
    }
    */
    
}