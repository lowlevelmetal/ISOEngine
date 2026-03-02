/**
 * ISOENGINE
 * engine.hpp
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ENGINE_H__
#define __ISOENGINE_ENGINE_H__

#include "object.h"

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

typedef struct isoengine {
    SDL_Window *window;
    SDL_Renderer *renderer;
    isoengine_object *objects;
    uint32_t object_count;
    uint32_t object_buffer_len; // Engine will prealloc space for objects for performance, so the object count will differ from the actual buffer size
    uint16_t width;
    uint16_t height;
} isoengine;

#endif