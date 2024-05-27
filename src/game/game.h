//
// Created by malo1 on 5/27/2024.
//

#pragma once

#include "context.h"

class game: public context {
public:
    game(unsigned int _width, unsigned int _height);

    void run();
private:
    void gameLoop();
};