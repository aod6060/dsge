#ifndef LW_H
#define LW_H

#include <lua.hpp>
#include <string>
#include <vector>
#include <map>

namespace lua_wrapper {

    enum LWType {
        LWT_INTEGER = 0,
        LWT_NUMBER,
        LWT_BOOL,
        LWT_STRING,
        LWT_MAX_SIZE
    };

    #define SVALUE_BUFFER_SIZE 1024

    struct LWVariable {
        std::string name;
        LWType type;
        int ivalue;
        float nvalue;
        bool bvalue;
        std::string svalue;
        // I hope this works. I'll for the moment limit a string to 1024 length.
        char svalue_buffer[SVALUE_BUFFER_SIZE];
    };

    struct LWState {
        std::string path;
        lua_State* state;
        //LWExports exports;
        //std::map<std::string, std::string> exports;
        std::vector<LWVariable> exports;

        void open();
        void open(std::string path);
        void close();
        void reload();

        int getInteger(std::string name);
        float getNumber(std::string name);
        bool getBoolean(std::string name);
        std::string getString(std::string name);

        void setInteger(std::string name, int value);
        void setNumber(std::string name, float value);
        void setBoolean(std::string name, bool value);
        void setString(std::string name, std::string value);

        // For now I don't care about arguments
        void callFunction(std::string name);
        void callUpdateFunction(float delta);

    };
}

#endif