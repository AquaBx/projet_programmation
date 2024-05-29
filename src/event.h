//
// Created by viann on 27/05/2024.
//
#pragma once

#include <SDL2/SDL_events.h>

namespace event {

    enum source : int32_t {
        player,
        fusee,
    };

    struct listener {
        explicit listener();

        virtual void handle_event(SDL_Event const &e) = 0;
    };

    namespace manager {

        void update();
        void append(source code, void* context = nullptr, void* context_2 = nullptr);

    } // namespace manager

} // namespace event
