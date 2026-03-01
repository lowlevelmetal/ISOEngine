/**
 * ISOENGINE
 * window.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"

bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height) {
    if(engine == nullptr || title == nullptr) {
        ERROR("Stop sending me nullptrs, thank you");
        return false;
    }

    ((isoengine*)engine)->width = width;
    ((isoengine*)engine)->height = height;

    if((((isoengine*)engine)->window = SDL_CreateWindow(title, width, height, 0)) == nullptr) {
        ERROR("Failed to create window");
        return false;
    }

    return true;
}