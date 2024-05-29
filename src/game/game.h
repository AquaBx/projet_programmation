//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <array>
#include <vector>

#include "event.h"
#include "camera.h"
#include "cluster.h"
#include "context.h"

#include "map/map.h"

#include "entity/entity.h"
#include "entity/interactible.h"

#include "GUI/health_bar.h"
#include "GUI/food_bar.h"


class game : public context, public event::listener {
public:
    enum class state {
        menu,
        game,
        game_over,
        victory,
    } current_state;

public:
    game(unsigned int _width, unsigned int _height);

    ~game() override;

    void handle_event(SDL_Event const &event) override;

    void run();

    static std::vector<gui_component *> ui_components;

protected:
    void update_game();
    void update_menu();
    void update_game_over();
    void update_victory();

private:
    uint32_t previous_tick;

    bool running = true;
};
