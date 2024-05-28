//
// Created by tomch on 27/05/2024.
//
#pragma once

#include "physics/circle.h"
#include "player.h"

class interactible {
protected:
    circle interact_zone;
public :
    interactible(float x, float y, float interact_r);

    const circle & get_interact_zone() const;

    virtual void interact(player * user) = 0;
};
