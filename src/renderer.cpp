//
// Created by viann on 27/05/2024.
//
#include "renderer.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "texture_manager.h"
#include "entity/sprite.h"
#include <SDL2/SDL_image.h>

namespace renderer {

    static SDL_Renderer* renderer = nullptr;

    bool initialize(void* window) {
        if(renderer) return true;

        renderer = SDL_CreateRenderer((SDL_Window*)window, -1, SDL_RENDERER_PRESENTVSYNC);
        if(!renderer) {
            std::cerr << "Error on SDL_CreateRenderer : " << SDL_GetError() << std::endl;
            return false;
        }

        if(auto code = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
            std::cerr << "Warning(code: " << code << ") could not set blend mode to SDL_BLENDMODE_BLEND : " << SDL_GetError() << std::endl;
        }

        return true;
    }

    void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void present() {
        SDL_RenderPresent(renderer);
    }

    void terminate() {
        SDL_DestroyRenderer(renderer);
        texture_manager::terminate();
    }

    void draw_rect(float x, float y, float width, float height, color c) {
        SDL_FRect rect { x, y, width, height };
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRectF(renderer, &rect);
    }


    void draw_texture(vec2<float> position, vec2<float> size, vec2<int> resolution, SDL_Texture* texture, vec2<int> frame) {
        SDL_Rect rect1 { frame.x*resolution.width, frame.y*resolution.height, resolution.width, resolution.height };
        SDL_FRect rect2 { position.x, position.y, size.width, size.height };

        SDL_RenderCopyF(renderer, texture, &rect1, &rect2);
    }

    // vérification
    int load_texture(const char * image_src, sprite * sprite_obj) {

        using std::cerr;
        using std::endl;

        SDL_Texture * texture;
        if(texture_manager::loaded_textures.find(image_src) != texture_manager::loaded_textures.end()) {
            texture = texture_manager::loaded_textures[image_src];
        } else {
            const char * ext = image_src;

            for ( ; *ext != '\0' ; ext ++ );
            for ( ; *ext != '.' ; ext -- );
            ext++;

            SDL_Surface* img = nullptr;

            if ( strcmp(ext,"png") == 0 ) {
                img = IMG_Load(image_src);
            }
            else if ( strcmp(ext,"bmp") == 0 ) {
                img = SDL_LoadBMP(image_src);
            }

            if (img == nullptr) {
                cerr << "SDL_Load Error: " << SDL_GetError() << endl;
                return EXIT_FAILURE;
            }

            texture = SDL_CreateTextureFromSurface(renderer, img);
            if (texture == nullptr) {
                cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
                return EXIT_FAILURE;
            }

            SDL_FreeSurface(img);
            texture_manager::loaded_textures[image_src] = texture;
        }

        sprite_obj->set_texture(texture);
        return 0;
    }
} // namespace renderer
