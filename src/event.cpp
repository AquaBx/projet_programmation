//
// Created by viann on 27/05/2024.
//
#include "event.h"

#include <vector>

namespace event {

    std::vector<listener *> listeners;

    listener::listener() {
        listeners.push_back(this);
    }

    namespace manager {

        void update() {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                for (auto listener: listeners) {
                    listener->handle_event(event);
                }
            }
        }

        void append(source code, void* context, void* context_2) {
            SDL_Event e;
            e.type = SDL_EventType ::SDL_USEREVENT;
            e.user.code = code;
            e.user.data1 = context;
            e.user.data2 = context_2;

            SDL_RegisterEvents(1);
            SDL_PushEvent(&e);
        }

    } // namespace manager

} // namespace event
