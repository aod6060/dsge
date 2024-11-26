#ifndef INPUT_H
#define INPUT_H


#include "SDL_events.h"
#include "SDL_gamecontroller.h"
#include <glm/glm.hpp>
#include <vector>

namespace input {
    enum InputState {
        IS_RELEASED = 0,
        IS_PRESSED_ONCE,
        IS_PRESSED,
        IS_RELEASED_ONCE,
        IS_MAX_SIZE
    };

    /*
        This enum is an edited version of the 
        KEYS.h file.
    */
    enum Keyboard {
        KEYS_UNKNOWN = 0,
        KEYS_A = 4,
        KEYS_B = 5,
        KEYS_C = 6,
        KEYS_D = 7,
        KEYS_E = 8,
        KEYS_F = 9,
        KEYS_G = 10,
        KEYS_H = 11,
        KEYS_I = 12,
        KEYS_J = 13,
        KEYS_K = 14,
        KEYS_L = 15,
        KEYS_M = 16,
        KEYS_N = 17,
        KEYS_O = 18,
        KEYS_P = 19,
        KEYS_Q = 20,
        KEYS_R = 21,
        KEYS_S = 22,
        KEYS_T = 23,
        KEYS_U = 24,
        KEYS_V = 25,
        KEYS_W = 26,
        KEYS_X = 27,
        KEYS_Y = 28,
        KEYS_Z = 29,
        KEYS_1 = 30,
        KEYS_2 = 31,
        KEYS_3 = 32,
        KEYS_4 = 33,
        KEYS_5 = 34,
        KEYS_6 = 35,
        KEYS_7 = 36,
        KEYS_8 = 37,
        KEYS_9 = 38,
        KEYS_0 = 39,
        KEYS_RETURN = 40,
        KEYS_ESCAPE = 41,
        KEYS_BACKSPACE = 42,
        KEYS_TAB = 43,
        KEYS_SPACE = 44,
        KEYS_MINUS = 45,
        KEYS_EQUALS = 46,
        KEYS_LEFTBRACKET = 47,
        KEYS_RIGHTBRACKET = 48,
        KEYS_BACKSLASH = 49,
        KEYS_NONUSHASH = 50,
        KEYS_SEMICOLON = 51,
        KEYS_APOSTROPHE = 52,
        KEYS_GRAVE = 53,
        KEYS_COMMA = 54,
        KEYS_PERIOD = 55,
        KEYS_SLASH = 56,
        KEYS_CAPSLOCK = 57,
        KEYS_F1 = 58,
        KEYS_F2 = 59,
        KEYS_F3 = 60,
        KEYS_F4 = 61,
        KEYS_F5 = 62,
        KEYS_F6 = 63,
        KEYS_F7 = 64,
        KEYS_F8 = 65,
        KEYS_F9 = 66,
        KEYS_F10 = 67,
        KEYS_F11 = 68,
        KEYS_F12 = 69,
        KEYS_PRINTSCREEN = 70,
        KEYS_SCROLLLOCK = 71,
        KEYS_PAUSE = 72,
        KEYS_INSERT = 73,
        KEYS_HOME = 74,
        KEYS_PAGEUP = 75,
        KEYS_DELETE = 76,
        KEYS_END = 77,
        KEYS_PAGEDOWN = 78,
        KEYS_RIGHT = 79,
        KEYS_LEFT = 80,
        KEYS_DOWN = 81,
        KEYS_UP = 82,
        KEYS_NUMLOCKCLEAR = 83,
        KEYS_KP_DIVIDE = 84,
        KEYS_KP_MULTIPLY = 85,
        KEYS_KP_MINUS = 86,
        KEYS_KP_PLUS = 87,
        KEYS_KP_ENTER = 88,
        KEYS_KP_1 = 89,
        KEYS_KP_2 = 90,
        KEYS_KP_3 = 91,
        KEYS_KP_4 = 92,
        KEYS_KP_5 = 93,
        KEYS_KP_6 = 94,
        KEYS_KP_7 = 95,
        KEYS_KP_8 = 96,
        KEYS_KP_9 = 97,
        KEYS_KP_0 = 98,
        KEYS_KP_PERIOD = 99,
        KEYS_NONUSBACKSLASH = 100,
        KEYS_APPLICATION = 101,
        KEYS_POWER = 102,
        KEYS_KP_EQUALS = 103,
        KEYS_F13 = 104,
        KEYS_F14 = 105,
        KEYS_F15 = 106,
        KEYS_F16 = 107,
        KEYS_F17 = 108,
        KEYS_F18 = 109,
        KEYS_F19 = 110,
        KEYS_F20 = 111,
        KEYS_F21 = 112,
        KEYS_F22 = 113,
        KEYS_F23 = 114,
        KEYS_F24 = 115,
        KEYS_EXECUTE = 116,
        KEYS_HELP = 117,
        KEYS_MENU = 118,
        KEYS_SELECT = 119,
        KEYS_STOP = 120,
        KEYS_AGAIN = 121,
        KEYS_UNDO = 122,
        KEYS_CUT = 123,
        KEYS_COPY = 124,
        KEYS_PASTE = 125,
        KEYS_FIND = 126,
        KEYS_MUTE = 127,
        KEYS_VOLUMEUP = 128,
        KEYS_VOLUMEDOWN = 129,
        KEYS_KP_COMMA = 133,
        KEYS_KP_EQUALSAS400 = 134,
        KEYS_INTERNATIONAL1 = 135,
        KEYS_INTERNATIONAL2 = 136,
        KEYS_INTERNATIONAL3 = 137,
        KEYS_INTERNATIONAL4 = 138,
        KEYS_INTERNATIONAL5 = 139,
        KEYS_INTERNATIONAL6 = 140,
        KEYS_INTERNATIONAL7 = 141,
        KEYS_INTERNATIONAL8 = 142,
        KEYS_INTERNATIONAL9 = 143,
        KEYS_LANG1 = 144,
        KEYS_LANG2 = 145,
        KEYS_LANG3 = 146,
        KEYS_LANG4 = 147,
        KEYS_LANG5 = 148,
        KEYS_LANG6 = 149,
        KEYS_LANG7 = 150,
        KEYS_LANG8 = 151,
        KEYS_LANG9 = 152,
        KEYS_ALTERASE = 153,
        KEYS_SYSREQ = 154,
        KEYS_CANCEL = 155,
        KEYS_CLEAR = 156,
        KEYS_PRIOR = 157,
        KEYS_RETURN2 = 158,
        KEYS_SEPARATOR = 159,
        KEYS_OUT = 160,
        KEYS_OPER = 161,
        KEYS_CLEARAGAIN = 162,
        KEYS_CRSEL = 163,
        KEYS_EXSEL = 164,
        KEYS_KP_00 = 176,
        KEYS_KP_000 = 177,
        KEYS_THOUSANDSSEPARATOR = 178,
        KEYS_DECIMALSEPARATOR = 179,
        KEYS_CURRENCYUNIT = 180,
        KEYS_CURRENCYSUBUNIT = 181,
        KEYS_KP_LEFTPAREN = 182,
        KEYS_KP_RIGHTPAREN = 183,
        KEYS_KP_LEFTBRACE = 184,
        KEYS_KP_RIGHTBRACE = 185,
        KEYS_KP_TAB = 186,
        KEYS_KP_BACKSPACE = 187,
        KEYS_KP_A = 188,
        KEYS_KP_B = 189,
        KEYS_KP_C = 190,
        KEYS_KP_D = 191,
        KEYS_KP_E = 192,
        KEYS_KP_F = 193,
        KEYS_KP_XOR = 194,
        KEYS_KP_POWER = 195,
        KEYS_KP_PERCENT = 196,
        KEYS_KP_LESS = 197,
        KEYS_KP_GREATER = 198,
        KEYS_KP_AMPERSAND = 199,
        KEYS_KP_DBLAMPERSAND = 200,
        KEYS_KP_VERTICALBAR = 201,
        KEYS_KP_DBLVERTICALBAR = 202,
        KEYS_KP_COLON = 203,
        KEYS_KP_HASH = 204,
        KEYS_KP_SPACE = 205,
        KEYS_KP_AT = 206,
        KEYS_KP_EXCLAM = 207,
        KEYS_KP_MEMSTORE = 208,
        KEYS_KP_MEMRECALL = 209,
        KEYS_KP_MEMCLEAR = 210,
        KEYS_KP_MEMADD = 211,
        KEYS_KP_MEMSUBTRACT = 212,
        KEYS_KP_MEMMULTIPLY = 213,
        KEYS_KP_MEMDIVIDE = 214,
        KEYS_KP_PLUSMINUS = 215,
        KEYS_KP_CLEAR = 216,
        KEYS_KP_CLEARENTRY = 217,
        KEYS_KP_BINARY = 218,
        KEYS_KP_OCTAL = 219,
        KEYS_KP_DECIMAL = 220,
        KEYS_KP_HEXADECIMAL = 221,
        KEYS_LCTRL = 224,
        KEYS_LSHIFT = 225,
        KEYS_LALT = 226,
        KEYS_LGUI = 227,
        KEYS_RCTRL = 228,
        KEYS_RSHIFT = 229,
        KEYS_RALT = 230,
        KEYS_RGUI = 231,
        KEYS_MODE = 257,
        KEYS_AUDIONEXT = 258,
        KEYS_AUDIOPREV = 259,
        KEYS_AUDIOSTOP = 260,
        KEYS_AUDIOPLAY = 261,
        KEYS_AUDIOMUTE = 262,
        KEYS_MEDIASELECT = 263,
        KEYS_WWW = 264,
        KEYS_MAIL = 265,
        KEYS_CALCULATOR = 266,
        KEYS_COMPUTER = 267,
        KEYS_AC_SEARCH = 268,
        KEYS_AC_HOME = 269,
        KEYS_AC_BACK = 270,
        KEYS_AC_FORWARD = 271,
        KEYS_AC_STOP = 272,
        KEYS_AC_REFRESH = 273,
        KEYS_AC_BOOKMARKS = 274,
        KEYS_BRIGHTNESSDOWN = 275,
        KEYS_BRIGHTNESSUP = 276,
        KEYS_DISPLAYSWITCH = 277,
        KEYS_KBDILLUMTOGGLE = 278,
        KEYS_KBDILLUMDOWN = 279,
        KEYS_KBDILLUMUP = 280,
        KEYS_EJECT = 281,
        KEYS_SLEEP = 282,
        KEYS_APP1 = 283,
        KEYS_APP2 = 284,
        KEYS_AUDIOREWIND = 285,
        KEYS_AUDIOFASTFORWARD = 286,
        KEYS_SOFTLEFT = 287,
        KEYS_SOFTRIGHT = 288,
        KEYS_ENDCALL = 290,
        KEYS_MAX_SIZE = 512
    };

    enum MouseButtons {
        MBS_LEFT = 0,
        MBS_CENTER,
        MBS_RIGHT,
        MBS_MAX_SIZE
    };

    struct InputMapping {
        int input;
        bool isMouse;
    };

    void init();
    void handleEvent(SDL_Event* e);
    void update(float delta);
    void release();

    // Keyboard
    bool isKeyReleased(const Keyboard& key);
    bool isKeyPressedOnce(const Keyboard& key);
    bool isKeyPressed(const Keyboard& key);
    bool isKeyReleasedOnce(const Keyboard& key);

    // Mouse
    bool isMouseButtonReleased(const MouseButtons& mb);
    bool isMouseButtonPressedOnce(const MouseButtons& mb);
    bool isMouseButtonPressed(const MouseButtons& mb);
    bool isMouseButtonReleasedOnce(const MouseButtons& mb);

    glm::vec2 getPosition();
    glm::vec2 getRelative();

    glm::vec2 getMouseWheel();

    void setGrab(bool grab);
    bool getGrab();
    void toggleGrab();

    // Input Mapping
    void initInputMapping(InputMapping* mapping, int input, bool isMouse=false);

    // Basic InputMapping function
    bool isInputMappingReleased(InputMapping* mapping);
    bool isInputMappingPressedOnce(InputMapping* mapping);
    bool isInputMappingPressed(InputMapping* mapping);
    bool isInputMappingReleasedOnce(InputMapping* mapping);

    // Axis Functions
    float getInputMappingAxisReleased(InputMapping* negative, InputMapping* positive);
    float getInputMappingAxisPressedOnce(InputMapping* negative, InputMapping* positive);
    float getInputMappingAxisPressed(InputMapping* negative, InputMapping* positive);
    float getInputMappingAxisReleasedOnce(InputMapping* negative, InputMapping* positive);

    // Value Functions
    float getInputMappingValueReleased(InputMapping* mapping);
    float getInputMappingValuePressedOnce(InputMapping* mapping);
    float getInputMappingValuePressed(InputMapping* mapping);
    float getInputMappingValueReleasedOnce(InputMapping* mapping);

    // Regular boolean check
    bool isInputMappingReleased(std::string name);
    bool isInputMappingPressedOnce(std::string name);
    bool isInputMappingPressed(std::string name);
    bool isInputMappingReleasedOnce(std::string name);

    // Axis Functions
    float getInputMappingAxisReleased(std::string negative, std::string positive);
    float getInputMappingAxisPressedOnce(std::string negative, std::string positive);
    float getInputMappingAxisPressed(std::string negative, std::string positive);
    float getInputMappingAxisReleasedOnce(std::string negative, std::string positive);

    // Value Functions
    float getInputMappingValueReleased(std::string name);
    float getInputMappingValuePressedOnce(std::string name);
    float getInputMappingValuePressed(std::string name);
    float getInputMappingValueReleasedOnce(std::string name);

    namespace gamepad {
        enum PlayerControllerName {
			PCN_PLAYER_1 = 0,
			PCN_PLAYER_2,
			PCN_PLAYER_3,
			PCN_PLAYER_4,
			PCN_PLAYER_MAX_SIZE
        };

        enum ControllerButton {
			CB_INVALID = -1,
			CB_A,
			CB_B,
			CB_X,
			CB_Y,
			CB_BACK,
			CB_GUIDE,
			CB_START,
			CB_LEFTSTICK,
			CB_RIGHTSTICK,
			CB_LEFTSHOULDER,
			CB_RIGHTSHOULDER,
			CB_DPAD_UP,
			CB_DPAD_DOWN,
			CB_DPAD_LEFT,
			CB_DPAD_RIGHT,
			CB_MISC1,
			CB_PADDLE1,
			CB_PADDLE2,
			CB_PADDLE3,
			CB_PADDLE4,
			CB_TOUCHPAD,
			CB_MAX_SIZE
        };


        struct PlayerControllerData {
            SDL_GameController* controller = nullptr;
            SDL_GameControllerType gamePadType;
            PlayerControllerName name;
            // -1.0f -> 1.0f
            glm::vec2 leftAxis;
            // -1.0f -> 1.0f
            glm::vec2 rightAxis;
            // 0.0f -> 1.0f
            float leftTrigger;
            // 0.0f -> 1.0f
            float rightTrigger;
            // Input Buttons
            std::vector<InputState> cButtons;
        };

        void init();
        void release();
        void handleEvent(SDL_Event* e);
        void update();

        glm::vec2 getLeftAxis(PlayerControllerName name);
        glm::vec2 getRightAxis(PlayerControllerName name);

        float getLeftTriggerAxis(PlayerControllerName name);
        float getRightTriggerAxis(PlayerControllerName name);

        bool isButtonReleased(PlayerControllerName name, ControllerButton button);
        bool isButtonPressedOnce(PlayerControllerName name, ControllerButton button);
        bool isButtonPressed(PlayerControllerName name, ControllerButton button);
        bool isButtonReleasedOnce(PlayerControllerName name, ControllerButton button);

        bool isControllerConnected(PlayerControllerName name);


        /*
            Input mapping for gamepad
        */
        struct InputMapping {
            PlayerControllerName name;
            ControllerButton button;
        };
        

        void initInputMapping(InputMapping* mapping, PlayerControllerName name, ControllerButton button);
        
        // Regular boolean check
        bool isInputMappingReleased(InputMapping* mapping);
        bool isInputMappingPressedOnce(InputMapping* mapping);
        bool isInputMappingPressed(InputMapping* mapping);
        bool isInputMappingReleasedOnce(InputMapping* mapping);

        // Axis Functions
        float getInputMappingAxisReleased(InputMapping* negative, InputMapping* positive);
        float getInputMappingAxisPressedOnce(InputMapping* negative, InputMapping* positive);
        float getInputMappingAxisPressed(InputMapping* negative, InputMapping* positive);
        float getInputMappingAxisReleasedOnce(InputMapping* negative, InputMapping* positive);

        // Value Functions
        float getInputMappingValueReleased(InputMapping* mapping);
        float getInputMappingValuePressedOnce(InputMapping* mapping);
        float getInputMappingValuePressed(InputMapping* mapping);
        float getInputMappingValueReleasedOnce(InputMapping* mapping);


        // Regular boolean check
        bool isInputMappingReleased(PlayerControllerName name, std::string mapping);
        bool isInputMappingPressedOnce(PlayerControllerName name, std::string mapping);
        bool isInputMappingPressed(PlayerControllerName name, std::string mapping);
        bool isInputMappingReleasedOnce(PlayerControllerName name, std::string mapping);

        // Axis Functions
        float getInputMappingAxisReleased(PlayerControllerName name, std::string negative, std::string positive);
        float getInputMappingAxisPressedOnce(PlayerControllerName name, std::string negative, std::string positive);
        float getInputMappingAxisPressed(PlayerControllerName name, std::string negative, std::string positive);
        float getInputMappingAxisReleasedOnce(PlayerControllerName name, std::string negative, std::string positive);

        // Value Functions
        float getInputMappingValueReleased(PlayerControllerName name, std::string mapping);
        float getInputMappingValuePressedOnce(PlayerControllerName name, std::string mapping);
        float getInputMappingValuePressed(PlayerControllerName name, std::string mapping);
        float getInputMappingValueReleasedOnce(PlayerControllerName name, std::string mapping);


    }
}

#endif