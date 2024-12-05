#include "lw_internal.h"


namespace lua_wrapper {

    // Gamepad Section
    std::map<std::string, input::gamepad::ControllerButton> cb_map = {
    {"CB_INVALID", input::gamepad::ControllerButton::CB_INVALID},
    {"CB_A", input::gamepad::ControllerButton::CB_A},
    {"CB_B", input::gamepad::ControllerButton::CB_B},
    {"CB_X", input::gamepad::ControllerButton::CB_X},
    {"CB_Y", input::gamepad::ControllerButton::CB_Y},
    {"CB_BACK", input::gamepad::ControllerButton::CB_BACK},
    {"CB_GUIDE", input::gamepad::ControllerButton::CB_GUIDE},
    {"CB_START", input::gamepad::ControllerButton::CB_START},
    {"CB_LEFTSTICK", input::gamepad::ControllerButton::CB_LEFTSTICK},
    {"CB_RIGHTSTICK", input::gamepad::ControllerButton::CB_RIGHTSTICK},
    {"CB_LEFTSHOULDER", input::gamepad::ControllerButton::CB_LEFTSHOULDER},
    {"CB_RIGHTSHOULDER", input::gamepad::ControllerButton::CB_RIGHTSHOULDER},
    {"CB_DPAD_UP", input::gamepad::ControllerButton::CB_DPAD_UP},
    {"CB_DPAD_DOWN", input::gamepad::ControllerButton::CB_DPAD_DOWN},
    {"CB_DPAD_LEFT", input::gamepad::ControllerButton::CB_DPAD_LEFT},
    {"CB_DPAD_RIGHT", input::gamepad::ControllerButton::CB_DPAD_RIGHT},
    {"CB_MISC1", input::gamepad::ControllerButton::CB_MISC1},
    {"CB_PADDLE1", input::gamepad::ControllerButton::CB_PADDLE1},
    {"CB_PADDLE2", input::gamepad::ControllerButton::CB_PADDLE2},
    {"CB_PADDLE3", input::gamepad::ControllerButton::CB_PADDLE3},
    {"CB_PADDLE4", input::gamepad::ControllerButton::CB_PADDLE4},
    {"CB_TOUCHPAD", input::gamepad::ControllerButton::CB_TOUCHPAD}
    };

    void lw_gamepad_initLib(LWState* state) {
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

        // Create ControllerButtons
        lua_newtable(state->state);

        for(std::map<std::string, input::gamepad::ControllerButton>::iterator it = cb_map.begin(); it != cb_map.end(); it++) {
            addIntegerToTable(state->state, it->first, it->second);
        }

        lua_setglobal(state->state, "ControllerButton");

        // Create GamepadPlayer1
        lua_newtable(state->state);

        addToTable(state->state, "getLeftAxis", lw_gamepad_player1_getLeftAxis);
        addToTable(state->state, "getRightAxis", lw_gamepad_player1_getRightAxis);
        addToTable(state->state, "getLeftTriggerAxis", lw_gamepad_player1_getLeftTriggerAxis);
        addToTable(state->state, "getRightTriggerAxis", lw_gamepad_player1_getRightTriggerAxis);
        addToTable(state->state, "isButtonReleased", lw_gamepad_player1_isButtonReleased);
        addToTable(state->state, "isButtonPressedOnce", lw_gamepad_player1_isButtonPressedOnce);
        addToTable(state->state, "isButtonPressed", lw_gamepad_player1_isButtonPressed);
        addToTable(state->state, "isButtonReleasedOnce", lw_gamepad_player1_isButtonReleasedOnce);
        addToTable(state->state, "isControllerConnect", lw_gamepad_player1_isControllerConnect);
        // InputMapping
        addToTable(state->state, "isInputMappingReleased", lw_gamepad_player1_isInputMappingReleased);
        addToTable(state->state, "isInputMappingPressedOnce", lw_gamepad_player1_isInputMappingPressedOnce);
        addToTable(state->state, "isInputMappingPressed", lw_gamepad_player1_isInputMappingPressed);
        addToTable(state->state, "isInputMappingReleasedOnce", lw_gamepad_player1_isInputMappingReleasedOnce);

        addToTable(state->state, "getInputMappingAxisRelease", lw_gamepad_player1_getInputMappingAxisRelease);
        addToTable(state->state, "getInputMappingAxisPressedOnce", lw_gamepad_player1_getInputMappingAxisPressedOnce);
        addToTable(state->state, "getInputMappingAxisPressed", lw_gamepad_player1_getInputMappingAxisPressed);
        addToTable(state->state, "getInputMappingAxisReleaseOnce", lw_gamepad_player1_getInputMappingAxisReleaseOnce);

        addToTable(state->state, "getInputMappingValueRelease", lw_gamepad_player1_getInputMappingValueRelease);
        addToTable(state->state, "getInputMappingValuePressedOnce", lw_gamepad_player1_getInputMappingValuePressedOnce);
        addToTable(state->state, "getInputMappingValuePressed", lw_gamepad_player1_getInputMappingValuePressed);
        addToTable(state->state, "getInputMappingValueReleaseOnce", lw_gamepad_player1_getInputMappingValueReleaseOnce);

        lua_setglobal(state->state, "GamepadPlayer1");

        // Create GamepadPlayer2
        lua_newtable(state->state);

        addToTable(state->state, "getLeftAxis", lw_gamepad_player2_getLeftAxis);
        addToTable(state->state, "getRightAxis", lw_gamepad_player2_getRightAxis);
        addToTable(state->state, "getLeftTriggerAxis", lw_gamepad_player2_getLeftTriggerAxis);
        addToTable(state->state, "getRightTriggerAxis", lw_gamepad_player2_getRightTriggerAxis);
        addToTable(state->state, "isButtonReleased", lw_gamepad_player2_isButtonReleased);
        addToTable(state->state, "isButtonPressedOnce", lw_gamepad_player2_isButtonPressedOnce);
        addToTable(state->state, "isButtonPressed", lw_gamepad_player2_isButtonPressed);
        addToTable(state->state, "isButtonReleasedOnce", lw_gamepad_player2_isButtonReleasedOnce);
        addToTable(state->state, "isControllerConnect", lw_gamepad_player2_isControllerConnect);
        // InputMapping
        addToTable(state->state, "isInputMappingReleased", lw_gamepad_player2_isInputMappingReleased);
        addToTable(state->state, "isInputMappingPressedOnce", lw_gamepad_player2_isInputMappingPressedOnce);
        addToTable(state->state, "isInputMappingPressed", lw_gamepad_player2_isInputMappingPressed);
        addToTable(state->state, "isInputMappingReleasedOnce", lw_gamepad_player2_isInputMappingReleasedOnce);


        addToTable(state->state, "getInputMappingAxisRelease", lw_gamepad_player2_getInputMappingAxisRelease);
        addToTable(state->state, "getInputMappingAxisPressedOnce", lw_gamepad_player2_getInputMappingAxisPressedOnce);
        addToTable(state->state, "getInputMappingAxisPressed", lw_gamepad_player2_getInputMappingAxisPressed);
        addToTable(state->state, "getInputMappingAxisReleaseOnce", lw_gamepad_player2_getInputMappingAxisReleaseOnce);

        addToTable(state->state, "getInputMappingValueRelease", lw_gamepad_player2_getInputMappingValueRelease);
        addToTable(state->state, "getInputMappingValuePressedOnce", lw_gamepad_player2_getInputMappingValuePressedOnce);
        addToTable(state->state, "getInputMappingValuePressed", lw_gamepad_player2_getInputMappingValuePressed);
        addToTable(state->state, "getInputMappingValueReleaseOnce", lw_gamepad_player2_getInputMappingValueReleaseOnce);

        lua_setglobal(state->state, "GamepadPlayer2");

        // Create GamepadPlayer3
        lua_newtable(state->state);

        addToTable(state->state, "getLeftAxis", lw_gamepad_player3_getLeftAxis);
        addToTable(state->state, "getRightAxis", lw_gamepad_player3_getRightAxis);
        addToTable(state->state, "getLeftTriggerAxis", lw_gamepad_player3_getLeftTriggerAxis);
        addToTable(state->state, "getRightTriggerAxis", lw_gamepad_player3_getRightTriggerAxis);
        addToTable(state->state, "isButtonReleased", lw_gamepad_player3_isButtonReleased);
        addToTable(state->state, "isButtonPressedOnce", lw_gamepad_player3_isButtonPressedOnce);
        addToTable(state->state, "isButtonPressed", lw_gamepad_player3_isButtonPressed);
        addToTable(state->state, "isButtonReleasedOnce", lw_gamepad_player3_isButtonReleasedOnce);
        addToTable(state->state, "isControllerConnect", lw_gamepad_player3_isControllerConnect);
        // InputMapping
        addToTable(state->state, "isInputMappingReleased", lw_gamepad_player3_isInputMappingReleased);
        addToTable(state->state, "isInputMappingPressedOnce", lw_gamepad_player3_isInputMappingPressedOnce);
        addToTable(state->state, "isInputMappingPressed", lw_gamepad_player3_isInputMappingPressed);
        addToTable(state->state, "isInputMappingReleasedOnce", lw_gamepad_player3_isInputMappingReleasedOnce);


        addToTable(state->state, "getInputMappingAxisRelease", lw_gamepad_player3_getInputMappingAxisRelease);
        addToTable(state->state, "getInputMappingAxisPressedOnce", lw_gamepad_player3_getInputMappingAxisPressedOnce);
        addToTable(state->state, "getInputMappingAxisPressed", lw_gamepad_player3_getInputMappingAxisPressed);
        addToTable(state->state, "getInputMappingAxisReleaseOnce", lw_gamepad_player3_getInputMappingAxisReleaseOnce);

        addToTable(state->state, "getInputMappingValueRelease", lw_gamepad_player3_getInputMappingValueRelease);
        addToTable(state->state, "getInputMappingValuePressedOnce", lw_gamepad_player3_getInputMappingValuePressedOnce);
        addToTable(state->state, "getInputMappingValuePressed", lw_gamepad_player3_getInputMappingValuePressed);
        addToTable(state->state, "getInputMappingValueReleaseOnce", lw_gamepad_player3_getInputMappingValueReleaseOnce);

        lua_setglobal(state->state, "GamepadPlayer3");

        // Create GamepadPlayer4
        lua_newtable(state->state);

        addToTable(state->state, "getLeftAxis", lw_gamepad_player4_getLeftAxis);
        addToTable(state->state, "getRightAxis", lw_gamepad_player4_getRightAxis);
        addToTable(state->state, "getLeftTriggerAxis", lw_gamepad_player4_getLeftTriggerAxis);
        addToTable(state->state, "getRightTriggerAxis", lw_gamepad_player4_getRightTriggerAxis);
        addToTable(state->state, "isButtonReleased", lw_gamepad_player4_isButtonReleased);
        addToTable(state->state, "isButtonPressedOnce", lw_gamepad_player4_isButtonPressedOnce);
        addToTable(state->state, "isButtonPressed", lw_gamepad_player4_isButtonPressed);
        addToTable(state->state, "isButtonReleasedOnce", lw_gamepad_player4_isButtonReleasedOnce);
        addToTable(state->state, "isControllerConnect", lw_gamepad_player4_isControllerConnect);
        // InputMapping
        addToTable(state->state, "isInputMappingReleased", lw_gamepad_player4_isInputMappingReleased);
        addToTable(state->state, "isInputMappingPressedOnce", lw_gamepad_player4_isInputMappingPressedOnce);
        addToTable(state->state, "isInputMappingPressed", lw_gamepad_player4_isInputMappingPressed);
        addToTable(state->state, "isInputMappingReleasedOnce", lw_gamepad_player4_isInputMappingReleasedOnce);


        addToTable(state->state, "getInputMappingAxisRelease", lw_gamepad_player4_getInputMappingAxisRelease);
        addToTable(state->state, "getInputMappingAxisPressedOnce", lw_gamepad_player4_getInputMappingAxisPressedOnce);
        addToTable(state->state, "getInputMappingAxisPressed", lw_gamepad_player4_getInputMappingAxisPressed);
        addToTable(state->state, "getInputMappingAxisReleaseOnce", lw_gamepad_player4_getInputMappingAxisReleaseOnce);

        addToTable(state->state, "getInputMappingValueRelease", lw_gamepad_player4_getInputMappingValueRelease);
        addToTable(state->state, "getInputMappingValuePressedOnce", lw_gamepad_player4_getInputMappingValuePressedOnce);
        addToTable(state->state, "getInputMappingValuePressed", lw_gamepad_player4_getInputMappingValuePressed);
        addToTable(state->state, "getInputMappingValueReleaseOnce", lw_gamepad_player4_getInputMappingValueReleaseOnce);

        lua_setglobal(state->state, "GamepadPlayer4");

    }

    
    // glm::vec2 getLeftAxis(PlayerControllerName name);
    int lw_gamepad_player1_getLeftAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player2_getLeftAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_2);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player3_getLeftAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_3);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player4_getLeftAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_4);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }


    // glm::vec2 getRightAxis(PlayerControllerName name);
    int lw_gamepad_player1_getRightAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getRightAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player2_getRightAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getRightAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_2);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player3_getRightAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getRightAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_3);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }

    int lw_gamepad_player4_getRightAxis(lua_State* l) {
        glm::vec2 axis = input::gamepad::getRightAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_4);
        lua_pushnumber(l, axis.x);
        lua_pushnumber(l, axis.y);
        return 2;
    }


    // float getLeftTriggerAxis(PlayerControllerName name);
    int lw_gamepad_player1_getLeftTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getLeftTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player2_getLeftTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getLeftTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_2);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player3_getLeftTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getLeftTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_3);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player4_getLeftTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getLeftTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_4);
        lua_pushnumber(l, trigger);
        return 1;
    }


    // float getRightTriggerAxis(PlayerControllerName name);
    int lw_gamepad_player1_getRightTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getRightTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player2_getRightTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getRightTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_2);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player3_getRightTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getRightTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_3);
        lua_pushnumber(l, trigger);
        return 1;
    }

    int lw_gamepad_player4_getRightTriggerAxis(lua_State* l) {
        float trigger = input::gamepad::getRightTriggerAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_4);
        lua_pushnumber(l, trigger);
        return 1;
    }


    // bool isButtonReleased(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonReleased(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isButtonReleased(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_2, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isButtonReleased(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_3, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isButtonReleased(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_4, cb);
        lua_pushboolean(l, ret);
        return 1;
    }


    // bool isButtonPressedOnce(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonPressedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isButtonPressedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isButtonPressedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isButtonPressedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, cb);
        lua_pushboolean(l, ret);
        return 1;
    }


    // bool isButtonPressed(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonPressed(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_1, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isButtonPressed(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_2, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isButtonPressed(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_3, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isButtonPressed(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_4, cb);
        lua_pushboolean(l, ret);
        return 1;
    }


    // bool isButtonReleasedOnce(PlayerControllerName name, ControllerButton button);
    int lw_gamepad_player1_isButtonReleasedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isButtonReleasedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isButtonReleasedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, cb);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isButtonReleasedOnce(lua_State* l) {
        input::gamepad::ControllerButton cb = (input::gamepad::ControllerButton)lua_tointeger(l, 1);
        bool ret = input::gamepad::isButtonReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, cb);
        lua_pushboolean(l, ret);
        return 1;
    }



    // bool isControllerConnected(PlayerControllerName name);
    int lw_gamepad_player1_isControllerConnect(lua_State* l) {
        bool ret = input::gamepad::isControllerConnected(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isControllerConnect(lua_State* l) {
        bool ret = input::gamepad::isControllerConnected(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isControllerConnect(lua_State* l) {
        bool ret = input::gamepad::isControllerConnected(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isControllerConnect(lua_State* l) {
        bool ret = input::gamepad::isControllerConnected(input::gamepad::PlayerControllerName::PCN_PLAYER_1);
        lua_pushboolean(l, ret);
        return 1;
    }

    // Regular boolean check
    //bool isInputMappingReleased(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isInputMappingReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isInputMappingReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isInputMappingReleased(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    //bool isInputMappingPressedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingPressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isInputMappingPressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isInputMappingPressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isInputMappingPressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    //bool isInputMappingPressed(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingPressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isInputMappingPressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isInputMappingPressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isInputMappingPressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    //bool isInputMappingReleasedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_isInputMappingReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player2_isInputMappingReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player3_isInputMappingReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    int lw_gamepad_player4_isInputMappingReleasedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        bool ret = input::gamepad::isInputMappingReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name);
        lua_pushboolean(l, ret);
        return 1;
    }

    // Axis Functions
    //float getInputMappingAxisReleased(PlayerControllerName name, std::string negative, std::string positive);
    int lw_gamepad_player1_getInputMappingAxisRelease(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, negative, positive));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingAxisRelease(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_2, negative, positive));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingAxisRelease(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_3, negative, positive));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingAxisRelease(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_4, negative, positive));
        return 1;
    }


    //float getInputMappingAxisPressedOnce(PlayerControllerName name, std::string negative, std::string positive);
    int lw_gamepad_player1_getInputMappingAxisPressedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, negative, positive));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingAxisPressedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, negative, positive));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingAxisPressedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, negative, positive));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingAxisPressedOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, negative, positive));
        return 1;
    }


    //float getInputMappingAxisPressed(PlayerControllerName name, std::string negative, std::string positive);
    int lw_gamepad_player1_getInputMappingAxisPressed(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_1, negative, positive));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingAxisPressed(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_2, negative, positive));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingAxisPressed(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_3, negative, positive));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingAxisPressed(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisPressed(input::gamepad::PlayerControllerName::PCN_PLAYER_4, negative, positive));
        return 1;
    }


    //float getInputMappingAxisReleasedOnce(PlayerControllerName name, std::string negative, std::string positive);
    int lw_gamepad_player1_getInputMappingAxisReleaseOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, negative, positive));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingAxisReleaseOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, negative, positive));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingAxisReleaseOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, negative, positive));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingAxisReleaseOnce(lua_State* l) {
        std::string negative = lua_tostring(l, 1);
        std::string positive = lua_tostring(l, 2);
        //glm::vec2 value = input::gamepad::getInputMappingAxisReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name);
        lua_pushnumber(l, input::gamepad::getInputMappingAxisReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, negative, positive));
        return 1;
    }


    // Value Functions
    //float getInputMappingValueReleased(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_getInputMappingValueRelease(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingValueRelease(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingValueRelease(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingValueRelease(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleased(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name));
        return 1;
    }


    //float getInputMappingValuePressedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_getInputMappingValuePressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingValuePressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingValuePressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingValuePressedOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name));
        return 1;
    }


    //float getInputMappingValuePressed(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_getInputMappingValuePressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressed(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingValuePressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressed(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingValuePressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressed(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingValuePressed(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValuePressed(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name));
        return 1;
    }


    //float getInputMappingValueReleasedOnce(PlayerControllerName name, std::string mapping);
    int lw_gamepad_player1_getInputMappingValueReleaseOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, name));
        return 1;
    }

    int lw_gamepad_player2_getInputMappingValueReleaseOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_2, name));
        return 1;
    }

    int lw_gamepad_player3_getInputMappingValueReleaseOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_3, name));
        return 1;
    }

    int lw_gamepad_player4_getInputMappingValueReleaseOnce(lua_State* l) {
        std::string name = lua_tostring(l, 1);
        lua_pushnumber(l, input::gamepad::getInputMappingValueReleasedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_4, name));
        return 1;
    }


}