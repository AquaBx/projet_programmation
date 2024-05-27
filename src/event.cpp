//
// Created by viann on 27/05/2024.
//
#include "event.h"

#include <vector>

namespace event {

    std::vector<listener*> listeners;

    listener::listener() {
        listeners.push_back(this);
    }

    namespace manager {

        void update() {
            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                for(auto listener : listeners) {
                    listener->handle_event(event);
                }
            }
        }

    } // namespace manager

} // namespace event
