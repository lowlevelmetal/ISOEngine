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
#include <time.h>

typedef struct isoengine {
    struct timespec prev;
    SDL_Window *window;
    SDL_Renderer *renderer;
    isoengine_object2d *objects2d;
    uint32_t *free_stack;         // Stack of free slot indices
    uint32_t free_stack_top;      // Index of top of free stack (0 = empty)
    uint32_t object2d_count;
    uint32_t object2d_buffer_len;
    uint16_t width;
    uint16_t height;
} isoengine;

#endif