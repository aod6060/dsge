#include "lw.h"
#include "lw_internal.h"
#include <map>
#include <string>


namespace lw {

    void LuaExports::init(LuaState* state) {
        this->parent = state;
    }

    void LuaExports::release() {
        this->parent = nullptr;
    }


    void LuaExports::setInt8(std::string name, int8_t value) {
        this->export_int8[name] = value;
    }

    void LuaExports::setUInt8(std::string name, uint8_t value) {
        this->export_uint8[name] = value;
    }

    void LuaExports::setInt16(std::string name, int16_t value) {
        this->export_int16[name] = value;
    }

    void LuaExports::setUInt16(std::string name, uint16_t value) {
        this->export_uint16[name] = value;
    }

    void LuaExports::setInt32(std::string name, int32_t value) {
        this->export_int32[name] = value;
    }

    void LuaExports::setUInt32(std::string name, uint32_t value) {
        this->export_uint32[name] = value;
    }

    void LuaExports::setInt64(std::string name, int64_t value) {
        this->export_int64[name] = value;
    }

    void LuaExports::setUInt64(std::string name, uint64_t value) {
        this->export_uint64[name] = value;
    }

    void LuaExports::setFloat(std::string name, float value) {
        this->export_float[name] = value;
    }

    void LuaExports::setDouble(std::string name, double value) {
        this->export_double[name] = value;
    }

    void LuaExports::setBool(std::string name, bool value) {
        this->export_bool[name] = value;
    }

    int8_t LuaExports::getInt8(std::string name) {
        return this->export_int8.at(name);
    }

    uint8_t LuaExports::getUInt8(std::string name) {
        return this->export_uint8.at(name);
    }

    int16_t LuaExports::getInt16(std::string name) {
        return this->export_int16.at(name);
    }

    uint16_t LuaExports::getUInt16(std::string name) {
        return this->export_uint16.at(name);
    }

    int32_t LuaExports::getInt32(std::string name) {
        return this->export_int32.at(name);
    }

    uint32_t LuaExports::getUInt32(std::string name) {
        return this->export_uint32.at(name);
    }

    int64_t LuaExports::getInt64(std::string name) {
        return this->export_int64.at(name);
    }

    uint64_t LuaExports::getUInt64(std::string name) {
        return this->export_uint64.at(name);
    }

    float LuaExports::getFloat(std::string name) {
        return this->export_float.at(name);
    }

    double LuaExports::getDouble(std::string name) {
        return this->export_double.at(name);
    }

    bool LuaExports::getBool(std::string name) {
        return this->export_bool.at(name);
    }

    void LuaExports::getAllInt8(std::vector<LuaExportVariable<int8_t>>& variables) {
        for(std::map<std::string, int8_t>::iterator it = export_int8.begin(); it != export_int8.end(); it++) {
            variables.push_back(LuaExportVariable<int8_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllUInt8(std::vector<LuaExportVariable<uint8_t>>& variables) {
        for(std::map<std::string, uint8_t>::iterator it = export_uint8.begin(); it != export_uint8.end(); it++) {
            variables.push_back(LuaExportVariable<uint8_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllInt16(std::vector<LuaExportVariable<int16_t>>& variables) {
        for(std::map<std::string, int16_t>::iterator it = export_int16.begin(); it != export_int16.end(); it++) {
            variables.push_back(LuaExportVariable<int16_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllUInt16(std::vector<LuaExportVariable<uint16_t>>& variables) {
        for(std::map<std::string, uint16_t>::iterator it = export_uint16.begin(); it != export_uint16.end(); it++) {
            variables.push_back(LuaExportVariable<uint16_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllInt32(std::vector<LuaExportVariable<int32_t>>& variables) {
        for(std::map<std::string, int32_t>::iterator it = export_int32.begin(); it != export_int32.end(); it++) {
            variables.push_back(LuaExportVariable<int32_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllUInt32(std::vector<LuaExportVariable<uint32_t>>& variables) {
        for(std::map<std::string, uint32_t>::iterator it = export_uint32.begin(); it != export_uint32.end(); it++) {
            variables.push_back(LuaExportVariable<uint32_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllInt64(std::vector<LuaExportVariable<int64_t>>& variables) {
        for(std::map<std::string, int64_t>::iterator it = export_int64.begin(); it != export_int64.end(); it++) {
            variables.push_back(LuaExportVariable<int64_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllUInt64(std::vector<LuaExportVariable<uint64_t>>& variables) {
        for(std::map<std::string, uint64_t>::iterator it = export_uint64.begin(); it != export_uint64.end(); it++) {
            variables.push_back(LuaExportVariable<uint64_t>(it->first, it->second));
        }
    }

    void LuaExports::getAllFloat(std::vector<LuaExportVariable<float>>& variables) {
        for(std::map<std::string, float>::iterator it = export_float.begin(); it != export_float.end(); it++) {
            variables.push_back(LuaExportVariable<float>(it->first, it->second));
        }
    }

    void LuaExports::getAllDouble(std::vector<LuaExportVariable<double>>& variables) {
        for(std::map<std::string, double>::iterator it = export_double.begin(); it != export_double.end(); it++) {
            variables.push_back(LuaExportVariable<double>(it->first, it->second));
        }
    }

    void LuaExports::getAllBool(std::vector<LuaExportVariable<bool>>& variables) {
        for(std::map<std::string, bool>::iterator it = export_bool.begin(); it != export_bool.end(); it++) {
            variables.push_back(LuaExportVariable<bool>(it->first, it->second));
        }
    }

}