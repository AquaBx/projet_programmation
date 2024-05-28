//
// Created by viann on 27/05/2024.
//
#include "renderer.h"
#include <iostream>


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

    int load_texture(const char * image_src, sprite * sprite_obj) {
        using std::cerr;
        using std::endl;

        SDL_Surface* bmp = SDL_LoadBMP(image_src);
        if (bmp == nullptr)
        {
            cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
            return EXIT_FAILURE;
        }

        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, bmp);
        if (texture == nullptr) {
            cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
            return EXIT_FAILURE;
        }

        sprite_obj->set_texture(texture);

        SDL_FreeSurface(bmp);
        return 0;
    }
} // namespace renderer
