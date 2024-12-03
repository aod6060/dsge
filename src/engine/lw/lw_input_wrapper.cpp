#include "lw_internal.h"

namespace lua_wrapper {

    std::map<std::string, input::Keyboard> keys_map = {
    {"KEYS_UNKNOWN", input::Keyboard::KEYS_UNKNOWN},
    {"KEYS_A", input::Keyboard::KEYS_A},
    {"KEYS_B", input::Keyboard::KEYS_B},
    {"KEYS_C", input::Keyboard::KEYS_C},
    {"KEYS_D", input::Keyboard::KEYS_D},
    {"KEYS_E", input::Keyboard::KEYS_E},
    {"KEYS_F", input::Keyboard::KEYS_F},
    {"KEYS_G", input::Keyboard::KEYS_G},
    {"KEYS_H", input::Keyboard::KEYS_H},
    {"KEYS_I", input::Keyboard::KEYS_I},
    {"KEYS_J", input::Keyboard::KEYS_J},
    {"KEYS_K", input::Keyboard::KEYS_K},
    {"KEYS_L", input::Keyboard::KEYS_L},
    {"KEYS_M", input::Keyboard::KEYS_M},
    {"KEYS_N", input::Keyboard::KEYS_N},
    {"KEYS_O", input::Keyboard::KEYS_O},
    {"KEYS_P", input::Keyboard::KEYS_P},
    {"KEYS_Q", input::Keyboard::KEYS_Q},
    {"KEYS_R", input::Keyboard::KEYS_R},
    {"KEYS_S", input::Keyboard::KEYS_S},
    {"KEYS_T", input::Keyboard::KEYS_T},
    {"KEYS_U", input::Keyboard::KEYS_U},
    {"KEYS_V", input::Keyboard::KEYS_V},
    {"KEYS_W", input::Keyboard::KEYS_W},
    {"KEYS_X", input::Keyboard::KEYS_X},
    {"KEYS_Y", input::Keyboard::KEYS_Y},
    {"KEYS_Z", input::Keyboard::KEYS_Z},
    {"KEYS_1", input::Keyboard::KEYS_1},
    {"KEYS_2", input::Keyboard::KEYS_2},
    {"KEYS_3", input::Keyboard::KEYS_3},
    {"KEYS_4", input::Keyboard::KEYS_4},
    {"KEYS_5", input::Keyboard::KEYS_5},
    {"KEYS_6", input::Keyboard::KEYS_6},
    {"KEYS_7", input::Keyboard::KEYS_7},
    {"KEYS_8", input::Keyboard::KEYS_8},
    {"KEYS_9", input::Keyboard::KEYS_9},
    {"KEYS_0", input::Keyboard::KEYS_0},
    {"KEYS_RETURN", input::Keyboard::KEYS_RETURN},
    {"KEYS_ESCAPE", input::Keyboard::KEYS_ESCAPE},
    {"KEYS_BACKSPACE", input::Keyboard::KEYS_BACKSPACE},
    {"KEYS_TAB", input::Keyboard::KEYS_TAB},
    {"KEYS_SPACE", input::Keyboard::KEYS_SPACE},
    {"KEYS_MINUS", input::Keyboard::KEYS_MINUS},
    {"KEYS_EQUALS", input::Keyboard::KEYS_EQUALS},
    {"KEYS_LEFTBRACKET", input::Keyboard::KEYS_LEFTBRACKET},
    {"KEYS_RIGHTBRACKET", input::Keyboard::KEYS_RIGHTBRACKET},
    {"KEYS_BACKSLASH", input::Keyboard::KEYS_BACKSLASH},
    {"KEYS_NONUSHASH", input::Keyboard::KEYS_NONUSHASH},
    {"KEYS_SEMICOLON", input::Keyboard::KEYS_SEMICOLON},
    {"KEYS_APOSTROPHE", input::Keyboard::KEYS_APOSTROPHE},
    {"KEYS_GRAVE", input::Keyboard::KEYS_GRAVE},
    {"KEYS_COMMA", input::Keyboard::KEYS_COMMA},
    {"KEYS_PERIOD", input::Keyboard::KEYS_PERIOD},
    {"KEYS_SLASH", input::Keyboard::KEYS_SLASH},
    {"KEYS_CAPSLOCK", input::Keyboard::KEYS_CAPSLOCK},
    {"KEYS_F1", input::Keyboard::KEYS_F1},
    {"KEYS_F2", input::Keyboard::KEYS_F2},
    {"KEYS_F3", input::Keyboard::KEYS_F3},
    {"KEYS_F4", input::Keyboard::KEYS_F4},
    {"KEYS_F5", input::Keyboard::KEYS_F5},
    {"KEYS_F6", input::Keyboard::KEYS_F6},
    {"KEYS_F7", input::Keyboard::KEYS_F7},
    {"KEYS_F8", input::Keyboard::KEYS_F8},
    {"KEYS_F9", input::Keyboard::KEYS_F9},
    {"KEYS_F10", input::Keyboard::KEYS_F10},
    {"KEYS_F11", input::Keyboard::KEYS_F11},
    {"KEYS_F12", input::Keyboard::KEYS_F12},
    {"KEYS_PRINTSCREEN", input::Keyboard::KEYS_PRINTSCREEN},
    {"KEYS_SCROLLLOCK", input::Keyboard::KEYS_SCROLLLOCK},
    {"KEYS_PAUSE", input::Keyboard::KEYS_PAUSE},
    {"KEYS_INSERT", input::Keyboard::KEYS_INSERT},
    {"KEYS_HOME", input::Keyboard::KEYS_HOME},
    {"KEYS_PAGEUP", input::Keyboard::KEYS_PAGEUP},
    {"KEYS_DELETE", input::Keyboard::KEYS_DELETE},
    {"KEYS_END", input::Keyboard::KEYS_END},
    {"KEYS_PAGEDOWN", input::Keyboard::KEYS_PAGEDOWN},
    {"KEYS_RIGHT", input::Keyboard::KEYS_RIGHT},
    {"KEYS_LEFT", input::Keyboard::KEYS_LEFT},
    {"KEYS_DOWN", input::Keyboard::KEYS_DOWN},
    {"KEYS_UP", input::Keyboard::KEYS_UP},
    {"KEYS_NUMLOCKCLEAR", input::Keyboard::KEYS_NUMLOCKCLEAR},
    {"KEYS_KP_DIVIDE", input::Keyboard::KEYS_KP_DIVIDE},
    {"KEYS_KP_MULTIPLY", input::Keyboard::KEYS_KP_MULTIPLY},
    {"KEYS_KP_MINUS", input::Keyboard::KEYS_KP_MINUS},
    {"KEYS_KP_PLUS", input::Keyboard::KEYS_KP_PLUS},
    {"KEYS_KP_ENTER", input::Keyboard::KEYS_KP_ENTER},
    {"KEYS_KP_1", input::Keyboard::KEYS_KP_1},
    {"KEYS_KP_2", input::Keyboard::KEYS_KP_2},
    {"KEYS_KP_3", input::Keyboard::KEYS_KP_3},
    {"KEYS_KP_4", input::Keyboard::KEYS_KP_4},
    {"KEYS_KP_5", input::Keyboard::KEYS_KP_5},
    {"KEYS_KP_6", input::Keyboard::KEYS_KP_6},
    {"KEYS_KP_7", input::Keyboard::KEYS_KP_7},
    {"KEYS_KP_8", input::Keyboard::KEYS_KP_8},
    {"KEYS_KP_9", input::Keyboard::KEYS_KP_9},
    {"KEYS_KP_0", input::Keyboard::KEYS_KP_0},
    {"KEYS_KP_PERIOD", input::Keyboard::KEYS_KP_PERIOD},
    {"KEYS_NONUSBACKSLASH", input::Keyboard::KEYS_NONUSBACKSLASH},
    {"KEYS_APPLICATION", input::Keyboard::KEYS_APPLICATION},
    {"KEYS_POWER", input::Keyboard::KEYS_POWER},
    {"KEYS_KP_EQUALS", input::Keyboard::KEYS_KP_EQUALS},
    {"KEYS_F13", input::Keyboard::KEYS_F13},
    {"KEYS_F14", input::Keyboard::KEYS_F14},
    {"KEYS_F15", input::Keyboard::KEYS_F15},
    {"KEYS_F16", input::Keyboard::KEYS_F16},
    {"KEYS_F17", input::Keyboard::KEYS_F17},
    {"KEYS_F18", input::Keyboard::KEYS_F18},
    {"KEYS_F19", input::Keyboard::KEYS_F19},
    {"KEYS_F20", input::Keyboard::KEYS_F20},
    {"KEYS_F21", input::Keyboard::KEYS_F21},
    {"KEYS_F22", input::Keyboard::KEYS_F22},
    {"KEYS_F23", input::Keyboard::KEYS_F23},
    {"KEYS_F24", input::Keyboard::KEYS_F24},
    {"KEYS_EXECUTE", input::Keyboard::KEYS_EXECUTE},
    {"KEYS_HELP", input::Keyboard::KEYS_HELP},
    {"KEYS_MENU", input::Keyboard::KEYS_MENU},
    {"KEYS_SELECT", input::Keyboard::KEYS_SELECT},
    {"KEYS_STOP", input::Keyboard::KEYS_STOP},
    {"KEYS_AGAIN", input::Keyboard::KEYS_AGAIN},
    {"KEYS_UNDO", input::Keyboard::KEYS_UNDO},
    {"KEYS_CUT", input::Keyboard::KEYS_CUT},
    {"KEYS_COPY", input::Keyboard::KEYS_COPY},
    {"KEYS_PASTE", input::Keyboard::KEYS_PASTE},
    {"KEYS_FIND", input::Keyboard::KEYS_FIND},
    {"KEYS_MUTE", input::Keyboard::KEYS_MUTE},
    {"KEYS_VOLUMEUP", input::Keyboard::KEYS_VOLUMEUP},
    {"KEYS_VOLUMEDOWN", input::Keyboard::KEYS_VOLUMEDOWN},
    {"KEYS_KP_COMMA", input::Keyboard::KEYS_KP_COMMA},
    {"KEYS_KP_EQUALSAS400", input::Keyboard::KEYS_KP_EQUALSAS400},
    {"KEYS_INTERNATIONAL1", input::Keyboard::KEYS_INTERNATIONAL1},
    {"KEYS_INTERNATIONAL2", input::Keyboard::KEYS_INTERNATIONAL2},
    {"KEYS_INTERNATIONAL3", input::Keyboard::KEYS_INTERNATIONAL3},
    {"KEYS_INTERNATIONAL4", input::Keyboard::KEYS_INTERNATIONAL4},
    {"KEYS_INTERNATIONAL5", input::Keyboard::KEYS_INTERNATIONAL5},
    {"KEYS_INTERNATIONAL6", input::Keyboard::KEYS_INTERNATIONAL6},
    {"KEYS_INTERNATIONAL7", input::Keyboard::KEYS_INTERNATIONAL7},
    {"KEYS_INTERNATIONAL8", input::Keyboard::KEYS_INTERNATIONAL8},
    {"KEYS_INTERNATIONAL9", input::Keyboard::KEYS_INTERNATIONAL9},
    {"KEYS_LANG1", input::Keyboard::KEYS_LANG1},
    {"KEYS_LANG2", input::Keyboard::KEYS_LANG2},
    {"KEYS_LANG3", input::Keyboard::KEYS_LANG3},
    {"KEYS_LANG4", input::Keyboard::KEYS_LANG4},
    {"KEYS_LANG5", input::Keyboard::KEYS_LANG5},
    {"KEYS_LANG6", input::Keyboard::KEYS_LANG6},
    {"KEYS_LANG7", input::Keyboard::KEYS_LANG7},
    {"KEYS_LANG8", input::Keyboard::KEYS_LANG8},
    {"KEYS_LANG9", input::Keyboard::KEYS_LANG9},
    {"KEYS_ALTERASE", input::Keyboard::KEYS_ALTERASE},
    {"KEYS_SYSREQ", input::Keyboard::KEYS_SYSREQ},
    {"KEYS_CANCEL", input::Keyboard::KEYS_CANCEL},
    {"KEYS_CLEAR", input::Keyboard::KEYS_CLEAR},
    {"KEYS_PRIOR", input::Keyboard::KEYS_PRIOR},
    {"KEYS_RETURN2", input::Keyboard::KEYS_RETURN2},
    {"KEYS_SEPARATOR", input::Keyboard::KEYS_SEPARATOR},
    {"KEYS_OUT", input::Keyboard::KEYS_OUT},
    {"KEYS_OPER", input::Keyboard::KEYS_OPER},
    {"KEYS_CLEARAGAIN", input::Keyboard::KEYS_CLEARAGAIN},
    {"KEYS_CRSEL", input::Keyboard::KEYS_CRSEL},
    {"KEYS_EXSEL", input::Keyboard::KEYS_EXSEL},
    {"KEYS_KP_00", input::Keyboard::KEYS_KP_00},
    {"KEYS_KP_000", input::Keyboard::KEYS_KP_000},
    {"KEYS_THOUSANDSSEPARATOR", input::Keyboard::KEYS_THOUSANDSSEPARATOR},
    {"KEYS_DECIMALSEPARATOR", input::Keyboard::KEYS_DECIMALSEPARATOR},
    {"KEYS_CURRENCYUNIT", input::Keyboard::KEYS_CURRENCYUNIT},
    {"KEYS_CURRENCYSUBUNIT", input::Keyboard::KEYS_CURRENCYSUBUNIT},
    {"KEYS_KP_LEFTPAREN", input::Keyboard::KEYS_KP_LEFTPAREN},
    {"KEYS_KP_RIGHTPAREN", input::Keyboard::KEYS_KP_RIGHTPAREN},
    {"KEYS_KP_LEFTBRACE", input::Keyboard::KEYS_KP_LEFTBRACE},
    {"KEYS_KP_RIGHTBRACE", input::Keyboard::KEYS_KP_RIGHTBRACE},
    {"KEYS_KP_TAB", input::Keyboard::KEYS_KP_TAB},
    {"KEYS_KP_BACKSPACE", input::Keyboard::KEYS_KP_BACKSPACE},
    {"KEYS_KP_A", input::Keyboard::KEYS_KP_A},
    {"KEYS_KP_B", input::Keyboard::KEYS_KP_B},
    {"KEYS_KP_C", input::Keyboard::KEYS_KP_C},
    {"KEYS_KP_D", input::Keyboard::KEYS_KP_D},
    {"KEYS_KP_E", input::Keyboard::KEYS_KP_E},
    {"KEYS_KP_F", input::Keyboard::KEYS_KP_F},
    {"KEYS_KP_XOR", input::Keyboard::KEYS_KP_XOR},
    {"KEYS_KP_POWER", input::Keyboard::KEYS_KP_POWER},
    {"KEYS_KP_PERCENT", input::Keyboard::KEYS_KP_PERCENT},
    {"KEYS_KP_LESS", input::Keyboard::KEYS_KP_LESS},
    {"KEYS_KP_GREATER", input::Keyboard::KEYS_KP_GREATER},
    {"KEYS_KP_AMPERSAND", input::Keyboard::KEYS_KP_AMPERSAND},
    {"KEYS_KP_DBLAMPERSAND", input::Keyboard::KEYS_KP_DBLAMPERSAND},
    {"KEYS_KP_VERTICALBAR", input::Keyboard::KEYS_KP_VERTICALBAR},
    {"KEYS_KP_DBLVERTICALBAR", input::Keyboard::KEYS_KP_DBLVERTICALBAR},
    {"KEYS_KP_COLON", input::Keyboard::KEYS_KP_COLON},
    {"KEYS_KP_HASH", input::Keyboard::KEYS_KP_HASH},
    {"KEYS_KP_SPACE", input::Keyboard::KEYS_KP_SPACE},
    {"KEYS_KP_AT", input::Keyboard::KEYS_KP_AT},
    {"KEYS_KP_EXCLAM", input::Keyboard::KEYS_KP_EXCLAM},
    {"KEYS_KP_MEMSTORE", input::Keyboard::KEYS_KP_MEMSTORE},
    {"KEYS_KP_MEMRECALL", input::Keyboard::KEYS_KP_MEMRECALL},
    {"KEYS_KP_MEMCLEAR", input::Keyboard::KEYS_KP_MEMCLEAR},
    {"KEYS_KP_MEMADD", input::Keyboard::KEYS_KP_MEMADD},
    {"KEYS_KP_MEMSUBTRACT", input::Keyboard::KEYS_KP_MEMSUBTRACT},
    {"KEYS_KP_MEMMULTIPLY", input::Keyboard::KEYS_KP_MEMMULTIPLY},
    {"KEYS_KP_MEMDIVIDE", input::Keyboard::KEYS_KP_MEMDIVIDE},
    {"KEYS_KP_PLUSMINUS", input::Keyboard::KEYS_KP_PLUSMINUS},
    {"KEYS_KP_CLEAR", input::Keyboard::KEYS_KP_CLEAR},
    {"KEYS_KP_CLEARENTRY", input::Keyboard::KEYS_KP_CLEARENTRY},
    {"KEYS_KP_BINARY", input::Keyboard::KEYS_KP_BINARY},
    {"KEYS_KP_OCTAL", input::Keyboard::KEYS_KP_OCTAL},
    {"KEYS_KP_DECIMAL", input::Keyboard::KEYS_KP_DECIMAL},
    {"KEYS_KP_HEXADECIMAL", input::Keyboard::KEYS_KP_HEXADECIMAL},
    {"KEYS_LCTRL", input::Keyboard::KEYS_LCTRL},
    {"KEYS_LSHIFT", input::Keyboard::KEYS_LSHIFT},
    {"KEYS_LALT", input::Keyboard::KEYS_LALT},
    {"KEYS_LGUI", input::Keyboard::KEYS_LGUI},
    {"KEYS_RCTRL", input::Keyboard::KEYS_RCTRL},
    {"KEYS_RSHIFT", input::Keyboard::KEYS_RSHIFT},
    {"KEYS_RALT", input::Keyboard::KEYS_RALT},
    {"KEYS_RGUI", input::Keyboard::KEYS_RGUI},
    {"KEYS_MODE", input::Keyboard::KEYS_MODE},
    {"KEYS_AUDIONEXT", input::Keyboard::KEYS_AUDIONEXT},
    {"KEYS_AUDIOPREV", input::Keyboard::KEYS_AUDIOPREV},
    {"KEYS_AUDIOSTOP", input::Keyboard::KEYS_AUDIOSTOP},
    {"KEYS_AUDIOPLAY", input::Keyboard::KEYS_AUDIOPLAY},
    {"KEYS_AUDIOMUTE", input::Keyboard::KEYS_AUDIOMUTE},
    {"KEYS_MEDIASELECT", input::Keyboard::KEYS_MEDIASELECT},
    {"KEYS_WWW", input::Keyboard::KEYS_WWW},
    {"KEYS_MAIL", input::Keyboard::KEYS_MAIL},
    {"KEYS_CALCULATOR", input::Keyboard::KEYS_CALCULATOR},
    {"KEYS_COMPUTER", input::Keyboard::KEYS_COMPUTER},
    {"KEYS_AC_SEARCH", input::Keyboard::KEYS_AC_SEARCH},
    {"KEYS_AC_HOME", input::Keyboard::KEYS_AC_HOME},
    {"KEYS_AC_BACK", input::Keyboard::KEYS_AC_BACK},
    {"KEYS_AC_FORWARD", input::Keyboard::KEYS_AC_FORWARD},
    {"KEYS_AC_STOP", input::Keyboard::KEYS_AC_STOP},
    {"KEYS_AC_REFRESH", input::Keyboard::KEYS_AC_REFRESH},
    {"KEYS_AC_BOOKMARKS", input::Keyboard::KEYS_AC_BOOKMARKS},
    {"KEYS_BRIGHTNESSDOWN", input::Keyboard::KEYS_BRIGHTNESSDOWN},
    {"KEYS_BRIGHTNESSUP", input::Keyboard::KEYS_BRIGHTNESSUP},
    {"KEYS_DISPLAYSWITCH", input::Keyboard::KEYS_DISPLAYSWITCH},
    {"KEYS_KBDILLUMTOGGLE", input::Keyboard::KEYS_KBDILLUMTOGGLE},
    {"KEYS_KBDILLUMDOWN", input::Keyboard::KEYS_KBDILLUMDOWN},
    {"KEYS_KBDILLUMUP", input::Keyboard::KEYS_KBDILLUMUP},
    {"KEYS_EJECT", input::Keyboard::KEYS_EJECT},
    {"KEYS_SLEEP", input::Keyboard::KEYS_SLEEP},
    {"KEYS_APP1", input::Keyboard::KEYS_APP1},
    {"KEYS_APP2", input::Keyboard::KEYS_APP2},
    {"KEYS_AUDIOREWIND", input::Keyboard::KEYS_AUDIOREWIND},
    {"KEYS_AUDIOFASTFORWARD", input::Keyboard::KEYS_AUDIOFASTFORWARD},
    {"KEYS_SOFTLEFT", input::Keyboard::KEYS_SOFTLEFT},
    {"KEYS_SOFTRIGHT", input::Keyboard::KEYS_SOFTRIGHT},
    {"KEYS_ENDCALL", input::Keyboard::KEYS_ENDCALL}
    };

    std::map<std::string, input::MouseButtons> mb_map = {
    {"MBS_LEFT", input::MouseButtons::MBS_LEFT},
    {"MBS_CENTER", input::MouseButtons::MBS_CENTER},
    {"MBS_RIGHT", input::MouseButtons::MBS_RIGHT}
    };

    void lw_input_initLib(LWState* state) {
        // Function
        std::function<void(lua_State*, std::string, lua_CFunction)> addToTable = [](lua_State* l, std::string name, lua_CFunction func){
            lua_pushstring(l, name.c_str());
            lua_pushcfunction(l, func);
            lua_settable(l, -3);
        };

        // Integer
        std::function<void(lua_State*, std::string, lua_Integer)> addIntegerToTable = [](lua_State* l, std::string name, lua_Integer value) {
            lua_pushstring(l, name.c_str());
            lua_pushinteger(l, value);
            lua_settable(l, -3);
        };

        // Keyboard
        lua_newtable(state->state);

        for(std::map<std::string, input::Keyboard>::iterator it = keys_map.begin(); it != keys_map.end(); it++) {
            addIntegerToTable(state->state, it->first, it->second);
        }

        lua_setglobal(state->state, "Keyboard");

        // MouseButtons
        lua_newtable(state->state);

        for(std::map<std::string, input::MouseButtons>::iterator it = mb_map.begin(); it != mb_map.end(); it++) {
            addIntegerToTable(state->state, it->first, it->second);
        }

        lua_setglobal(state->state, "MouseButtons");

        // Input Functions
        lua_newtable(state->state);

        addToTable(state->state, "isKeyReleased", lw_input_isKeyReleased);
        addToTable(state->state, "isKeyPressedOnce", lw_input_isKeyPressedOnce);
        addToTable(state->state, "isKeyPressed", lw_input_isKeyPressed);
        addToTable(state->state, "isKeyReleasedOnce", lw_input_isKeyReleasedOnce);

        addToTable(state->state, "isMouseButtonReleased", lw_input_isMouseButtonReleased);
        addToTable(state->state, "isMouseButtonPressedOnce", lw_input_isMouseButtonPressedOnce);
        addToTable(state->state, "isMouseButtonPressed", lw_input_isMouseButtonPressed);
        addToTable(state->state, "isMouseButtonReleasedOnce", lw_input_isMouseButtonReleasedOnce);

        addToTable(state->state, "getPosition", lw_input_getPosition);
        addToTable(state->state, "getRelative", lw_input_getRelative);
        addToTable(state->state, "getMouseWheel", lw_input_getMouseWheel);

        addToTable(state->state, "setGrab", lw_input_setGrab);
        addToTable(state->state, "getGrab", lw_input_getGrab);
        addToTable(state->state, "toggleGrab", lw_input_toggleGrab);

        addToTable(state->state, "isInputMappingReleased", lw_input_isInputMappingReleased);
        addToTable(state->state, "isInputMappingPressedOnce", lw_input_isInputMappingPressedOnce);
        addToTable(state->state, "isInputMappingPressed", lw_input_isInputMappingPressed);
        addToTable(state->state, "isInputMappingReleasedOnce", lw_input_isInputMappingReleasedOnce);

        addToTable(state->state, "getInputMappingAxisReleased", lw_input_getInputMappingAxisReleased);
        addToTable(state->state, "getInputMappingAxisPressedOnce", lw_input_getInputMappingAxisPressedOnce);
        addToTable(state->state, "getInputMappingAxisPressed", lw_input_getInputMappingAxisPressed);
        addToTable(state->state, "getInputMappingAxisReleasedOnce", lw_input_getInputMappingAxisReleasedOnce);

        addToTable(state->state, "getInputMappingValueReleased", lw_input_getInputMappingValueReleased);
        addToTable(state->state, "getInputMappingValuePressedOnce", lw_input_getInputMappingValuePressedOnce);
        addToTable(state->state, "getInputMappingValuePressed", lw_input_getInputMappingValuePressed);
        addToTable(state->state, "getInputMappingValueReleasedOnce", lw_input_getInputMappingValueReleasedOnce);

        lua_setglobal(state->state, "Input");
    }

    int lw_input_isKeyReleased(lua_State* l) {
        input::Keyboard k  = (input::Keyboard)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isKeyReleased(k));
        return 1;
    }

    int lw_input_isKeyPressedOnce(lua_State* l) {
        input::Keyboard k  = (input::Keyboard)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isKeyPressedOnce(k));
        return 1;
    }

    int lw_input_isKeyPressed(lua_State* l) {
        input::Keyboard k  = (input::Keyboard)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isKeyPressed(k));
        return 1;
    }

    int lw_input_isKeyReleasedOnce(lua_State* l) {
        input::Keyboard k  = (input::Keyboard)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isKeyReleasedOnce(k));
        return 1;
    }

    int lw_input_isMouseButtonReleased(lua_State* l) {
        input::MouseButtons mb = (input::MouseButtons)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isMouseButtonReleased(mb));
        return 1;
    }

    int lw_input_isMouseButtonPressedOnce(lua_State* l) {
        input::MouseButtons mb = (input::MouseButtons)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isMouseButtonPressedOnce(mb));
        return 1;
    }

    int lw_input_isMouseButtonPressed(lua_State* l) {
        input::MouseButtons mb = (input::MouseButtons)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isMouseButtonPressed(mb));
        return 1;
    }

    int lw_input_isMouseButtonReleasedOnce(lua_State* l) {
        input::MouseButtons mb = (input::MouseButtons)lua_tointeger(l, 1);
        lua_pushboolean(l, input::isMouseButtonReleasedOnce(mb));
        return 1;
    }

    int lw_input_getPosition(lua_State* l) {
        lua_pushnumber(l, input::getPosition().x);
        lua_pushnumber(l, input::getPosition().y);
        return 2;
    }

    int lw_input_getRelative(lua_State* l) {
        lua_pushnumber(l, input::getRelative().x);
        lua_pushnumber(l, input::getRelative().y);
        return 2;
    }

    
    int lw_input_getMouseWheel(lua_State* l) {
        lua_pushnumber(l, input::getMouseWheel().x);
        lua_pushnumber(l, input::getMouseWheel().y);
        return 2;
    }

    int lw_input_setGrab(lua_State* l) {
        bool b = (bool)lua_toboolean(l, 1);
        input::setGrab(b);
        return 0;
    }

    int lw_input_getGrab(lua_State* l) {
        lua_pushboolean(l, input::getGrab());
        return 1;
    }

    int lw_input_toggleGrab(lua_State* l) {
        input::toggleGrab();
        return 0;
    }

    //bool isInputMappingReleased(std::string name);
    int lw_input_isInputMappingReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushboolean(l, input::isInputMappingReleased(name));
        return 1;
    }


    //bool isInputMappingPressedOnce(std::string name);
    int lw_input_isInputMappingPressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushboolean(l, input::isInputMappingPressedOnce(name));
        return 1;
    }


    //bool isInputMappingPressed(std::string name);
    int lw_input_isInputMappingPressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushboolean(l, input::isInputMappingPressed(name));
        return 1;
    }


    //bool isInputMappingReleasedOnce(std::string name);
    int lw_input_isInputMappingReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushboolean(l, input::isInputMappingPressedOnce(name));
        return 1;
    }


    // Axis Functions
    //float getInputMappingAxisReleased(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisReleased(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        lua_pushnumber(l, input::getInputMappingAxisReleased(negative, positive));
        return 1;
    }


    //float getInputMappingAxisPressedOnce(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisPressedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        lua_pushnumber(l, input::getInputMappingAxisPressedOnce(negative, positive));
        return 1;
    }


    //float getInputMappingAxisPressed(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisPressed(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        lua_pushnumber(l, input::getInputMappingAxisPressed(negative, positive));
        return 1;
    }


    //float getInputMappingAxisReleasedOnce(std::string negative, std::string positive);
    int lw_input_getInputMappingAxisReleasedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        lua_pushnumber(l, input::getInputMappingAxisReleasedOnce(negative, positive));
        return 1;
    }



    // Value Functions
    //float getInputMappingValueReleased(std::string name);
    int lw_input_getInputMappingValueReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::getInputMappingValueReleased(name));
        return 1;
    }


    //float getInputMappingValuePressedOnce(std::string name);
    int lw_input_getInputMappingValuePressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::getInputMappingValuePressedOnce(name));
        return 1;
    }


    //float getInputMappingValuePressed(std::string name);
    int lw_input_getInputMappingValuePressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::getInputMappingValuePressed(name));
        return 1;
    }


    //float getInputMappingValueReleasedOnce(std::string name);
    int lw_input_getInputMappingValueReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::getInputMappingValueReleasedOnce(name));
        return 1;
    }


}