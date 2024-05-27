//
// Created by celia on 27/05/2024.
//
#include "player.h"
#include "renderer.h"

player::player(float x, float y, float width, float height)
        : entity(x, y, width, height)  {}

player::~player(){}

void player::draw(){
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);
}

void player::update(float dt){
    const float speed = 10;
    move(speed * dt, 0);
}