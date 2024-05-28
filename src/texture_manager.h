//
// Created by malo1 on 5/28/2024.
//

#pragma once

#include <string>
#include <unordered_map>
#include "SDL_render.h"


namespace texture_manager {
    std::unordered_map<std::string, SDL_Texture*> loaded_textures;

    void terminate() {
        for(auto & loaded_texture : loaded_textures)
            SDL_DestroyTexture(loaded_texture.second);
    }
} // namespace texture_manager
