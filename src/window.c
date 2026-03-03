/**
 * ISOENGINE
 * window.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"
#include "macro.h"

#include <SDL3/SDL_render.h>

bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height) {
    isoengine *eng = (isoengine *)engine;
    
    if(eng == nullptr || title == nullptr) {
        ERROR("Stop sending me nullptrs, thank you");
        return false;
    }

    if(eng->window) {
        ERROR("You already have a window");
        return false;
    }

    eng->width = width;
    eng->height = height;

    if((eng->window = SDL_CreateWindow(title, width, height, 0)) == nullptr) {
        ERROR("Failed to create window --> %s", SDL_GetError());
        return false;
    }

    if((eng->renderer = SDL_CreateRenderer(eng->window, NULL)) == nullptr) {
        ERROR("Failed to create renderer --> %s", SDL_GetError());
        return false;
    }

    return true;
}