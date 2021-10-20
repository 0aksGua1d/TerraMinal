#pragma once

typedef struct {
    bool is_down : 1;
    bool is_held : 1;
} KeyState;

typedef struct {
    bool capslock: 1;
    bool left_alt: 1;
    bool right_alt: 1;
    bool left_control: 1;
    bool right_control: 1;
    bool shift: 1;
    bool numlock: 1;
    bool scroll_lock: 1;
} KeyEventFlags;
