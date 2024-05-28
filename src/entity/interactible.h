//
// Created by tomch on 27/05/2024.
//
#pragma once

#include "physics/circle.h"
#include "player.h"

class interactible
{
protected:
    circle interact_zone;

public :
    interactible(float x, float y, float interact_r);

    virtual circle get_interact_zone() const;

    virtual void interact(player* user) = 0;

    void draw_interact_zone(const camera & cam, vec2<float> position) const
    {
        float top = interact_zone.position.y-interact_zone.rayon;
        float right = interact_zone.position.x+interact_zone.rayon;
        float bottom = interact_zone.position.y+interact_zone.rayon;
        float left = interact_zone.position.x-interact_zone.rayon;
        aabb rel = {top,right,bottom,left};
        aabb abs = rel + position;

        vec4<float> monrect = cam.transform({{abs.left,abs.top}},{{abs.right-abs.left,abs.bottom-abs.top}});

        renderer::draw_rect(monrect.x,monrect.y,monrect.width,monrect.height);
    }
};
