#include "lw_internal.h"


namespace lua_wrapper {

    void LWState::open(std::string path) {
        this->path = path; // For reloading scripts

        this->exports.init(this);

        this->state = luaL_newstate();
    }

    void LWState::close() {
        lua_close(this->state);

        this->exports.release();
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