//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <SDL2/SDL_events.h>

#include "context.h"
#include "event.h"

#include "entity/player.h"

class game: public context, public event::listener {
public:
    game(unsigned int _width, unsigned int _height);
    virtual ~game() override;

    /* implémentation event::listener */
    virtual void handle_event(SDL_Event const& event) override;

    void run();
private:
    bool running = true;
    player * p;
};
