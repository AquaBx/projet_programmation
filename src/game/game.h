//
// Created by malo1 on 5/27/2024.
//

#pragma once

#include "context.h"
#include "entity/player.h"

class game: public context {
public:
    game(unsigned int _width, unsigned int _height);
    ~game();
    void run();
private:
    player * p;
};
