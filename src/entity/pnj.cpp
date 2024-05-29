//
// Created by tomch on 29/05/2024.
//

#include <iostream>
#include "pnj.h"
#include "map/map.h"

pnj::pnj(vec2<float> pos, vec2<float> size, float _max_health, aabb collide_box, vec2<uint32_t> frame_res,
         const char *image_src, std::vector<uint32_t> animation_lengths) :
        entity(pos),
        animated_sprite(pos, size, frame_res, {{size.x / 2, size.y / 2}}, image_src, animation_lengths, 0.1),
        collidable_entity(pos, collide_box),
        interactible(size.x / 2, size.y / 2, 16),
        position_initiale(pos),
        objectif(pos),
        max_health(_max_health),
        current_health(_max_health),
        tick(0.) {}

void pnj::draw(const camera &cam) const {
    //interactible::draw_interact_zone(cam, position);
    //collidable_entity::draw_collide_box(cam);

    renderer::draw_rect(objectif.x, objectif.y, 5, 5);
    sprite::draw(cam);
}

circle pnj::get_interact_zone() const {
    return interactible::get_interact_zone() + get_position();
}

void pnj::update(float dt) {
    if (tick == map::map_tick) return;
    tick = map::map_tick;

    animated_sprite::update(dt);

    vec2<float> dir = (objectif - position);

    const float speed = 10;

    if (dir.norme() < 5.f) {

        float rng1 = rand() / 32767.f - 0.5;
        float rng2 = rand() / 32767.f - 0.5;

        objectif = {{position_initiale.x + 100 * rng1, position_initiale.y + 100 * rng2}};
        return;
    };
    dir = dir.normalize();


    uint32_t idx = map::find_cluster_idx(get_position());
    std::vector<cluster *> m_clusters = map::get_surrounding_clusters(idx);

    vec2<float> dposx = {{dir.x * speed * dt, 0}};
    vec2<float> dposy = {{0, dir.y * speed * dt}};

    bool colx = physics::check_collide(this, dposx, m_clusters);
    bool coly = physics::check_collide(this, dposy, m_clusters);

    if (!colx) move(dposx.x, 0);
    if (!coly) move(0, dposy.y);

    if (!(colx && coly)) {
        unsigned int new_idx = map::find_cluster_idx(get_position());

        map::clusters[idx].foreground.erase(this);
        map::clusters[new_idx].foreground.insert(this);

        if (idx != new_idx) {
            map::clusters[idx].collidables.erase(this);
            map::clusters[new_idx].collidables.insert(this);

            map::clusters[idx].interactibles.erase(this);
            map::clusters[new_idx].interactibles.insert(this);
        }
    }
}

void pnj::damage(float damage_value) {
    current_health = std::max(current_health - damage_value, 0.f);
}

void pnj::heal(float heal_value) {
    current_health = std::min(heal_value + current_health, max_health);
}

float pnj::get_max_health() const {
    return max_health;
}

float pnj::get_current_health() const {
    return current_health;
}
