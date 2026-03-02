/**
 * ISOENGINE
 * engine.hpp
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ENGINE_H__
#define __ISOENGINE_ENGINE_H__

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

typedef struct isoengine {
    uint16_t width;
    uint16_t height;
    SDL_Window *window;
    SDL_Renderer *renderer;
} isoengine;

#endif