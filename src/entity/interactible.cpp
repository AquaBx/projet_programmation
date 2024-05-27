//
// Created by tomch on 27/05/2024.
//

#include "interactible.h"

interactible::interactible(float x, float y, float width, float height, float interact_r): entity(x,y,width,height) {
    interact_zone.rayon = interact_r;
    interact_zone.position = entity::position;
}

const circle & interactible::get_interact_zone() const{
    return interact_zone;
}
