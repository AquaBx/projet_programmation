//
// Created by tomch on 27/05/2024.
//

#pragma once

#include "entity.h"
#include "physics/circle.h"
#include "player.h"

class interactible : public entity {
protected:
    circle interact_zone;
public :
    interactible(float x, float y, float width, float height, float interact_r);

    ~interactible() override = default;

    const circle & get_interact_zone() const;

    virtual void interact(player * user) = 0;
};
