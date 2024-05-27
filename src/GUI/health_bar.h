//
// Created by celia on 27/05/2024.
//
#pragma once

#include "gui_component.h"
#include "renderer.h"
#include "entity/player.h"

class health_bar : public gui_component {
public :
    health_bar(player * p, const float x, const float y, const float width, const float height);

    virtual ~health_bar();

    void draw() override;
    void update(float dt) override;

private:
    const player * p;
    float current_health;
    float max_health;
};
