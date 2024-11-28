#include "lw.h"
#include "lua.h"
#include "lw_internal.h"


namespace lua_wrapper {

    void LWState::open(std::string path) {
        this->path = path; // For reloading scripts

        this->state = luaL_newstate();

        initLibs(this);

        int result = luaL_loadfile(this->state, this->path.c_str());

        if(result != LUA_OK) {
            const char* message = lua_tostring(state, -1);
            std::cout << message << "\n";
            lua_pop(this->state, 1);
        }

        result = lua_pcall(this->state, 0, LUA_MULTRET, 0);

        if(result != LUA_OK) {
            const char* message = lua_tostring(state, -1);
            std::cout << message << "\n";
            lua_pop(this->state, 1);
        }
    }

    void LWState::close() {
        lua_close(this->state);
    }


    void initLibs(LWState* state) {
        luaL_openlibs(state->state);

        lua_pushlightuserdata(state->state, state);
        lua_setglobal(state->state, "state");

        lua_pushcfunction(state->state, lw_export);
        lua_setglobal(state->state, "export");

        lua_newtable(state->state);

        lua_pushstring(state->state, "LWT_INTEGER");
        lua_pushinteger(state->state, LWType::LWT_INTEGER);
        lua_settable(state->state, -3);

        //lua_setglobal(state->state, "LWT_INTEGER");
        lua_pushstring(state->state, "LWT_NUMBER");
        lua_pushinteger(state->state, LWType::LWT_NUMBER);
        lua_settable(state->state, -3);

        //lua_setglobal(state->state, "LWT_NUMBER");
        lua_pushstring(state->state, "LWT_BOOL");
        lua_pushinteger(state->state, LWType::LWT_BOOL);
        lua_settable(state->state, -3);

        lua_setglobal(state->state, "LWType");

        //lua_setglobal(state->state, "LWT_BOOL");

        //export_initLibs(state);
    }

    int lw_export(lua_State* l) {
        LWState* state = (LWState*)lua_touserdata(l, 1);
        std::string name = lua_tostring(l, 2);
        LWType type = (LWType)lua_tointeger(l, 3);

        //state->exports[name] = name;
        LWVariable v;
        v.name = name;
        v.type = type;

        state->exports.push_back(v);

        return 0;
    }

    int LWState::getInteger(std::string name) {
        int value = 0;
        lua_getglobal(this->state, name.c_str());
        value = lua_tointeger(this->state, -1);
        lua_pop(this->state, -1);
        return value;
    }

    float LWState::getNumber(std::string name) {
        float value = 0.0f;
        lua_getglobal(this->state, name.c_str());
        value = lua_tonumber(this->state, -1);
        lua_pop(this->state, -1);
        return value;
    }

    bool LWState::getBoolean(std::string name) {
        bool value = false;
        lua_getglobal(this->state, name.c_str());
        value = lua_toboolean(this->state, -1);
        lua_pop(this->state, -1);
        return value;
    }

    void LWState::setInteger(std::string name, int value) {
        lua_pushinteger(this->state, value);
        lua_setglobal(this->state, name.c_str());
    }

    void LWState::setNumber(std::string name, float value) {
        lua_pushnumber(this->state, value);
        lua_setglobal(this->state, name.c_str());
    }

    void LWState::setBoolean(std::string name, bool value) {
        lua_pushboolean(this->state, value);
        lua_setglobal(this->state, name.c_str());
    }

    void LWState::callFunction(std::string name) {
        lua_getglobal(this->state, name.c_str());
        int result = lua_pcall(this->state, 0, 0, 0);

        if(result != LUA_OK) {
            std::string msg = lua_tostring(this->state, -1);
            std::cout << msg << "\n";
        }
    }
}