//
// Created by celia on 27/05/2024.
//
#include "player.h"
#include "renderer.h"

player::player(float x, float y, float width, float height, float interact_r)
        : entity(x, y, width, height)    {
    interact_zone.rayon = interact_r;
    interact_zone.position = entity::position;
}

const circle & player::get_interact_zone() const{
    return interact_zone;
}


player::~player(){}

void player::draw(){
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);
}

void player::update(float dt){
    const float speed = 10;
    move(speed * dt, 0);
}