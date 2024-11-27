#include "lw_internal.h"


namespace lua_wrapper {

    void LWState::open(std::string path) {
        this->path = path; // For reloading scripts

        this->exports.init(this);

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

        this->exports.release();
    }


    void initLibs(LWState* state) {
        luaL_openlibs(state->state);

        lua_pushlightuserdata(state->state, state);
        lua_setglobal(state->state, "state");

        export_initLibs(state);
    }

    /*
    void LuaState::open(std::string path) {
        //this->state = luaL_newstate();

        lua_State* s = ::luaL_newstate();

        ::lua_close(s);

    }

    void LuaState::close() {
        //lua_close(this->state);
    }
    */

    /*
    void initLibs(LuaState* state) {
        luaL_openlibs(state->state);
        export_initLibs(state);
    }
    */
}