//
// Created by tomch on 27/05/2024.
//

#include "interactible.h"

interactible::interactible(float x, float y, float interact_r)
        : interact_zone{interact_r, {{x, y}}} {
}

circle interactible::get_interact_zone() const {
    return interact_zone;
}
