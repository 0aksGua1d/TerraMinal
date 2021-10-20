#include "KeyboardMapping.h"

#include <map>
#include <windows.h>

static const std::map<int, std::wstring> key_mapping{
        {VK_BACK,      L"backspace"},
        {VK_TAB,       L"tab"},
        {VK_CLEAR,     L"clear"},
        {VK_RETURN,    L"enter"},
        {VK_SHIFT,     L"shift"},
        {VK_CONTROL,   L"control"},
        {VK_MENU,      L"alt"},
        {VK_PAUSE,     L"pause"},
        {VK_CAPITAL,   L"capslock"},
        {VK_ESCAPE,    L"escape"},
        {VK_SPACE,     L"space"},
        {VK_PRIOR,     L"pageup"},
        {VK_NEXT,      L"pagedown"},
        {VK_END,       L"end"},
        {VK_HOME,      L"home"},
        {VK_LEFT,      L"left_arrow"},
        {VK_UP,        L"up_arrow"},
        {VK_RIGHT,     L"right_arrow"},
        {VK_DOWN,      L"down_arrow"},
        {VK_SELECT,    L"select"},
        {VK_PRINT,     L"print"},
        {VK_SNAPSHOT,  L"printscreen"},
        {VK_INSERT,    L"insert"},
        {VK_DELETE,    L"delete"},
        {'0',          L"0"},
        {'1',          L"1"},
        {'2',          L"2"},
        {'3',          L"3"},
        {'4',          L"4"},
        {'5',          L"5"},
        {'6',          L"6"},
        {'7',          L"7"},
        {'8',          L"8"},
        {'9',          L"9"},
        {'A',          L"A"},
        {'B',          L"B"},
        {'C',          L"C"},
        {'D',          L"D"},
        {'E',          L"E"},
        {'F',          L"F"},
        {'G',          L"G"},
        {'H',          L"H"},
        {'I',          L"I"},
        {'J',          L"J"},
        {'K',          L"K"},
        {'L',          L"L"},
        {'M',          L"M"},
        {'N',          L"N"},
        {'O',          L"O"},
        {'P',          L"P"},
        {'Q',          L"Q"},
        {'R',          L"R"},
        {'S',          L"S"},
        {'T',          L"T"},
        {'U',          L"U"},
        {'V',          L"V"},
        {'W',          L"W"},
        {'X',          L"X"},
        {'Y',          L"Y"},
        {'Z',          L"Z"},
        {VK_LWIN,      L"left_windows"},
        {VK_RWIN,      L"right_windows"},
        {VK_NUMPAD0,   L"numpad_0"},
        {VK_NUMPAD1,   L"numpad_1"},
        {VK_NUMPAD2,   L"numpad_2"},
        {VK_NUMPAD3,   L"numpad_3"},
        {VK_NUMPAD4,   L"numpad_4"},
        {VK_NUMPAD5,   L"numpad_5"},
        {VK_NUMPAD6,   L"numpad_6"},
        {VK_NUMPAD7,   L"numpad_7"},
        {VK_NUMPAD8,   L"numpad_8"},
        {VK_NUMPAD9,   L"numpad_9"},
        {VK_MULTIPLY,  L"*"},
        {VK_ADD,       L"+"},
        {VK_SEPARATOR, L"separator"},
        {VK_SUBTRACT,  L"-"},
        {VK_DECIMAL,   L"decimal"},
        {VK_DIVIDE,    L"/"},
        {VK_F1,        L"f1"},
        {VK_F2,        L"f2"},
        {VK_F3,        L"f3"},
        {VK_F4,        L"f4"},
        {VK_F5,        L"f5"},
        {VK_F6,        L"f6"},
        {VK_F7,        L"f7"},
        {VK_F8,        L"f8"},
        {VK_F9,        L"f9"},
        {VK_F10,       L"f10"},
        {VK_F11,       L"f11"},
        {VK_F12,       L"f12"},
        {VK_F13,       L"f13"},
        {VK_F14,       L"f14"},
        {VK_F15,       L"f15"},
        {VK_F16,       L"f16"},
        {VK_F17,       L"f17"},
        {VK_F18,       L"f18"},
        {VK_F19,       L"f19"},
        {VK_F20,       L"f20"},
        {VK_F21,       L"f21"},
        {VK_F22,       L"f22"},
        {VK_F23,       L"f23"},
        {VK_F24,       L"f24"},
        {VK_NUMLOCK,   L"numlock"},
        {VK_SCROLL,    L"scroll_lock"},
        {VK_LSHIFT,    L"left_shift"},
        {VK_RSHIFT,    L"right_shift"},
        {VK_LCONTROL,  L"left_control"},
        {VK_RCONTROL,  L"right_control"},
        {VK_LMENU,     L"left_alt"},
        {VK_RMENU,     L"right_alt"},
};

const std::map<int, std::wstring>& KeyboardMapping::get_key_mapping() { return key_mapping; }


static std::map<std::wstring, int> inverse_key_mapping;

const std::map<std::wstring, int>& KeyboardMapping::get_key_inverse_mapping() {
    if (inverse_key_mapping.empty()) {
        for (auto&[k, v] : key_mapping) {
            inverse_key_mapping.insert({v, k});
        }
    }
    return inverse_key_mapping;
}