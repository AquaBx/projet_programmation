//
// Created by tomch on 28/05/2024.
//

#include "cow.h"

#include <algorithm>
#include "renderer.h"
#include "input.h"
#include "map/map.h"

cow::cow(vec2<float> pos, vec2<float> size, float max_health):
    entity(pos),
    animated_sprite(pos, size, {{32, 32}}, {{size.x/2, size.y/2}}, "../resources/cow.png", {3, 3, 2}, 0.1),
    collidable_entity(pos, aabb{24, 24, 32, 8}),
    interactible(16, 16, 32),
    max_health(max_health), current_health(max_health)
{
}

void cow::draw(const camera& cam) const
{
    //interactible::draw_interact_zone(cam, position);
    //collidable_entity::draw_collide_box(cam);
    sprite::draw(cam);
}

circle cow::get_interact_zone() const
{
    return interactible::get_interact_zone() + get_position();
}

void cow::update(float dt)
{
    animated_sprite::update(dt);

    if (delai_interact >= max_delai_interact)
    {
        sprite_offset.y = 0;
    }
    else
    {
        delai_interact += dt;
    }

//    vec2<float> dir{{1, 0}};
//
//    const float speed = 10;
//
//    if (dir.x == 0 && dir.y == 0) return;
//
//    uint32_t idx = map::find_cluster_idx(get_position());
//    std::vector<cluster*> m_clusters = map::get_surrounding_clusters(idx);
//
//    vec2<float> dposx = {{dir.x * speed * dt, 0}};
//    vec2<float> dposy = {{0, dir.y * speed * dt}};
//
//    bool colx = physics::check_collide(this, dposx, m_clusters);
//    bool coly = physics::check_collide(this, dposy, m_clusters);
//
//    if (!colx) move(dposx.x, 0);
//    if (!coly) move(0, dposy.y);
//
//    if (!(colx && coly))
//    {
//        unsigned int new_idx = map::find_cluster_idx(get_position());
//
//        map::clusters[idx].foreground.erase(this);
//        map::clusters[new_idx].foreground.insert(this);
//
//        if (idx != new_idx)
//        {
//            map::clusters[idx].collidables.erase(this);
//            map::clusters[new_idx].collidables.insert(this);
//
//            map::clusters[idx].interactibles.erase(this);
//            map::clusters[new_idx].interactibles.insert(this);
//        }
//    }
}

void cow::damage(float damage_value)
{
    current_health = std::max(current_health - damage_value, 0.f);
}

void cow::benefit(float benefit_value)
{
    current_health = std::min(benefit_value + current_health, max_health);
}

float cow::get_max_health() const
{
    return max_health;
}

float cow::get_current_health() const
{
    return current_health;
}
