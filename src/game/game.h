//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <vector>
#include "context.h"
#include "entity/entity.h"
#include "entity/interactible.h"
#include <SDL2/SDL_events.h>
#include <array>
#include "event.h"
#include "entity/player.h"
#include "cluster.h"
#include "camera.h"
#include "GUI/health_bar.h"
#include "map/map.h"

class game: public context, public event::listener {
public:
    game(unsigned int _width, unsigned int _height);
    ~game() override;

    /* implémentation event::listener */
    virtual void handle_event(SDL_Event const& event) override;

    void run();

private:
    map m;
    std::vector<gui_component *> ui_components;

    // interactible * perceive(const player * user);

    bool running = true;

    player * p;
};
