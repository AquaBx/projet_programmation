//
// Created by tomch on 29/05/2024.
//

#include "fusee.h"

//
// Created by tomch on 28/05/2024.
//

#include "cow.h"

#include <algorithm>
#include "renderer.h"
#include "input.h"
#include "map/map.h"

fusee::fusee(vec2<float> pos, vec2<float> size, float max_health) :
        entity(pos),
        animated_sprite(pos, size, {{48, 48}}, {{size.x / 2, size.y / 2}}, "../resources/fusee.png", {1, 1, 2, 2, 2},
                        0.1),
        collidable_entity(pos, aabb{20, 39, 41, 9}),
        interactible(24, 30, 20),
        max_health(max_health), current_health(max_health) {
}

void fusee::draw(const camera &cam) const {
    //interactible::draw_interact_zone(cam, position);
    //collidable_entity::draw_collide_box(cam);
    sprite::draw(cam);
}

circle fusee::get_interact_zone() const {
    return interactible::get_interact_zone() + get_position();
}

void fusee::update(float dt) {
    animated_sprite::update(dt);

    return;

    vec2<float> dir{{1, 0}};

    const float speed = 10;

    if (dir.x == 0 && dir.y == 0) return;

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

void fusee::damage(float damage_value) {
    current_health = std::max(current_health - damage_value, 0.f);
}

void fusee::heal(float heal_value) {
    current_health = std::min(heal_value + current_health, max_health);
}

float fusee::get_max_health() const {
    return max_health;
}

float fusee::get_current_health() const {
    return current_health;
}
