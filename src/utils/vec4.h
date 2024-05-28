//
// Created by viann on 28/05/2024.
//
#pragma once

template <class T>
union vec4 {
    struct {
        T x, y, z, w;
    };
    struct {
        T _[2];
        T width, height;
    };
    struct {
        T r, g, b, a;
    };
};
