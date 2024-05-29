//
// Created by malo1 on 5/28/2024.
//

#include "input.h"
#include "SDL_keyboard.h"
#include <cassert>

static int32_t keyboard_size = 0;
static const uint8_t *keyboard_state = nullptr;

void input::initialize() {
    keyboard_state = SDL_GetKeyboardState(&keyboard_size);
    assert(keyboard_state != nullptr && "Failed to initialize keyboard");
}

bool input::is_key_pressed(SDL_Scancode scancode) {
    assert(scancode < keyboard_size);
    return keyboard_state[scancode];
}