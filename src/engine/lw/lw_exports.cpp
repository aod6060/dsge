#include "lw_internal.h"



namespace lua_wrapper {
    
    void LWExports::init(LWState* state) {
        this->parent = state;
    }

    void LWExports::release() {
        this->parent = nullptr;
    }

    void LWExports::setInteger(std::string name, int32_t value) {
        this->export_int[name] = value;
    }

    void LWExports::setNumber(std::string name, float value) {
        this->export_num[name] = value;
    }

    void LWExports::setBool(std::string name, bool value) {
        this->export_bool[name] = value;
    }

    int32_t LWExports::getInteger(std::string name) {
        return this->export_int.at(name);
    }

    float LWExports::getNumber(std::string name) {
        return this->export_num.at(name);
    }

    bool LWExports::getBool(std::string name) {
        return this->export_bool.at(name);
    }

    void LWExports::getAllIntegers(std::vector<LWVariable<int32_t>>& variables) {
        for(std::map<std::string, int32_t>::iterator it = export_int.begin(); it != export_int.end(); it++) {
            variables.push_back(LWVariable<int32_t>(it->first, it->second));
        }
    }

    void LWExports::getAllNumbers(std::vector<LWVariable<float>>& variables) {
        for(std::map<std::string, float>::iterator it = export_num.begin(); it != export_num.end(); it++) {
            variables.push_back(LWVariable<float>(it->first, it->second));
        }
    }

    void LWExports::getAllBools(std::vector<LWVariable<bool>>& variables) {
        for(std::map<std::string, bool>::iterator it = export_bool.begin(); it != export_bool.end(); it++) {
            variables.push_back(LWVariable<bool>(it->first, it->second));
        }
    }
}