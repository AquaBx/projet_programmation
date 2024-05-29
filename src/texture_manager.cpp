//
// Created by viann on 28/05/2024.
//
#include "renderer.h"
#include "texture_manager.h"

#include <iostream>

namespace texture_manager {

    std::ifstream& operator>>(std::ifstream& is, atlases& a) {
        uint32_t val;
        is >> val;
        assert(val < (size_t)atlases::count && "Assertion Failed : value is not a valid atlas id !");
        a = (atlases)val;
        return is;
    }

#define ATLAS_PATH(next) "../resources/tiles/" next

    std::array<std::string, (size_t)atlases::count> atlases_name {
            ATLAS_PATH("tilemap.png")
    };

    std::unordered_map<std::string, SDL_Texture*> loaded_textures;

    void initialize_atlases() {
        for(const std::string& file : atlases_name) {
            SDL_Texture* tex = renderer::create_sdl_texture(file.c_str());
            if(!tex) {
                std::cerr << "Error, could not load " << file << " atlas !" << std::endl;
            }
            loaded_textures[file] = tex;
        }
    }

    void terminate() {
        for(auto & loaded_texture : loaded_textures)
            SDL_DestroyTexture(loaded_texture.second);
    }

} // texture_manager
