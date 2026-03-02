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

    if(!SDL_RenderPresent(eng->renderer)) {
        ERROR("Failed to present renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}