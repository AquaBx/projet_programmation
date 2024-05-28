//
// Created by celia on 27/05/2024.
//

#include "health_bar.h"

health_bar::health_bar(player * p, const float x, const float y, const float width, const float height)
        : gui_component(x, y, width, height), p(p), current_health(100.0f), max_health(p->get_max_health()) {}

health_bar::~health_bar() {}

void health_bar::draw() {
    // blue rectangle : area of the whole image
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::blue);

    // green rectangle : area of the bar (const)
    renderer::draw_rect(position.x + 10, position.y + 2, 29, 3, renderer::colors::red);

    // red rectangle : area of the bar (not const)
    float health_width = (current_health / max_health) * size.width;
    renderer::draw_rect(position.x + 10, position.y + 2, 29, 3, renderer::colors::green);
}

void health_bar::update(float dt) {
    current_health = p->get_current_health();
}

