/**
 * ISOENGINE
 * render.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"
#include "macro.h"

bool isoengine_render_draw(void *const engine) {
    isoengine *eng = (isoengine *)engine;

    if(eng == nullptr) {
        ERROR("Stop feeding me null pointers :(");
        return false;
    }

    if(eng->renderer == nullptr) {
        ERROR("Renderer is null, cannot draw :(");
        return false;
    }

    if(!SDL_RenderClear(eng->renderer)) {
        ERROR("Failed to clear renderer: %s", SDL_GetError());
        return false;
    }

    if(eng->objects2d) {
        uint32_t found = 0;
        for(size_t i = 0; i < eng->object2d_buffer_len && found < eng->object2d_count; i++) {
            if(!eng->objects2d[i].id) {
                continue;
            }
            found++;
            if(eng->objects2d[i].texture) {
                SDL_FRect rect = {};
                rect.x = eng->objects2d[i].coords.x;
                rect.y = eng->objects2d[i].coords.y;
                
                if(!SDL_GetTextureSize(eng->objects2d[i].texture, &rect.w, &rect.h)) {
                    ERROR("Failed to get texture size");
                    return false;
                }
                
                if(!SDL_RenderTexture(eng->renderer, eng->objects2d[i].texture, NULL, &rect)) {
                    ERROR("Failed to render texture");
                    return false;
                }
            }
        }
    }

    if(!SDL_RenderPresent(eng->renderer)) {
        ERROR("Failed to present renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}