#ifndef LW_H
#define LW_H

#include <lua.hpp>
#include <string>
#include <vector>
#include <map>

namespace lua_wrapper {

    struct LWState;

    template<typename T>
    struct LWVariable {
        std::string name;
        T value;

        LWVariable<T>() {}

        LWVariable<T>(std::string name, T value) {
            this->name = name;
            this->value = value;
        }
    };

    struct LWExports {
        LWState* parent;

        std::map<std::string, int32_t> export_int;
        std::map<std::string, float> export_num;
        std::map<std::string, bool> export_bool;

        void init(LWState* state);
        void release();

        // Setters
        void setInteger(std::string name, int32_t value);
        void setNumber(std::string name, float value);
        void setBool(std::string name, bool value);

        // Getters
        int32_t getInteger(std::string name);
        float getNumber(std::string name);
        bool getBool(std::string name);

        // This will get you all of the all variables
        void getAllIntegers(std::vector<LWVariable<int32_t>>& variables);
        void getAllNumbers(std::vector<LWVariable<float>>& variables);
        void getAllBools(std::vector<LWVariable<bool>>& variables);

    };

    struct LWState {
        std::string path;
        lua_State* state;
        LWExports exports;

        void open(std::string path);
        void close();
    };

    //struct LuaState;
    /*
    template<typename T>
    struct LuaExportVariable {
        std::string name;
        T value;

        LuaExportVariable<T>() {}

        LuaExportVariable<T>(std::string name, T value) {
            this->name = name;
            this->value = value;
        }
    };

    // These will act similar to glsl uniforms
    struct LuaExports {
        LuaState* parent = nullptr;

        std::map<std::string, int32_t> export_integers;
        std::map<std::string, float> export_numbers;
        std::map<std::string, bool> export_bools;

        // Going to need to figure out what other types
        // I'll be need here

        void init(LuaState* state);
        void release();

        // Setters
        void setInteger(std::string name, int32_t value);
        void setNumber(std::string name, float value);
        void setBool(std::string name, bool value);

        // Getters
        int32_t getInteger(std::string name);
        float getNumber(std::string name);
        bool getBool(std::string name);

        // This will get you all of the all variables
        void getAllIntegers(std::vector<LuaExportVariable<int32_t>>& variables);
        void getAllNumbers(std::vector<LuaExportVariable<float>>& variables);
        void getAllBools(std::vector<LuaExportVariable<bool>>& variables);

    };
    */
    /*
    struct LuaState {
        ///lua_State* state;
        //LuaExports exports;

        void open(std::string path);
        void close();
    };
    */

    //void test();

}

#endif