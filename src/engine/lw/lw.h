#ifndef LW_H
#define LW_H

#include <string>
#include <vector>
#include <map>
#include <lua.hpp>

namespace lw {

    struct LuaState;

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

        std::map<std::string, int8_t> export_int8;
        std::map<std::string, uint8_t> export_uint8;
        std::map<std::string, int16_t> export_int16;
        std::map<std::string, uint16_t> export_uint16;
        std::map<std::string, int32_t> export_int32;
        std::map<std::string, uint32_t> export_uint32;
        std::map<std::string, int64_t> export_int64;
        std::map<std::string, uint64_t> export_uint64;
        std::map<std::string, float> export_float;
        std::map<std::string, double> export_double;
        std::map<std::string, bool> export_bool;
        // Going to need to figure out what other types
        // I'll be need here

        void init(LuaState* state);
        void release();

        void setInt8(std::string name, int8_t value);
        void setUInt8(std::string name, uint8_t value);
        void setInt16(std::string name, int16_t value);
        void setUInt16(std::string name, uint16_t value);
        void setInt32(std::string name, int32_t value);
        void setUInt32(std::string name, uint32_t value);
        void setInt64(std::string name, int64_t value);
        void setUInt64(std::string name, uint64_t value);
        void setFloat(std::string name, float value);
        void setDouble(std::string name, double value);
        void setBool(std::string name, bool value);

        int8_t getInt8(std::string name);
        uint8_t getUInt8(std::string name);
        int16_t getInt16(std::string name);
        uint16_t getUInt16(std::string name);
        int32_t getInt32(std::string name);
        uint32_t getUInt32(std::string name);
        int64_t getInt64(std::string name);
        uint64_t getUInt64(std::string name);
        float getFloat(std::string name);
        double getDouble(std::string name);
        bool getBool(std::string name);

        // This will get you all of the all variables
        void getAllInt8(std::vector<LuaExportVariable<int8_t>>& variables);
        void getAllUInt8(std::vector<LuaExportVariable<uint8_t>>& variables);
        void getAllInt16(std::vector<LuaExportVariable<int16_t>>& variables);
        void getAllUInt16(std::vector<LuaExportVariable<uint16_t>>& variables);
        void getAllInt32(std::vector<LuaExportVariable<int32_t>>& variables);
        void getAllUInt32(std::vector<LuaExportVariable<uint32_t>>& variables);
        void getAllInt64(std::vector<LuaExportVariable<int64_t>>& variables);
        void getAllUInt64(std::vector<LuaExportVariable<uint64_t>>& variables);
        void getAllFloat(std::vector<LuaExportVariable<float>>& variables);
        void getAllDouble(std::vector<LuaExportVariable<double>>& variables);
        void getAllBool(std::vector<LuaExportVariable<bool>>& variables);

    };

    struct LuaState {
        lua_State* state;
        LuaExports exports;

        void open(std::string path);
        void close();
    };
}

#endif