/**
 * ISOENGINE
 * engine.hpp
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ENGINE_H__
#define __ISOENGINE_ENGINE_H__

#include <SDL3/SDL_video.h>

typedef struct isoengine {
    uint16_t width;
    uint16_t height;
    SDL_Window *window;
} isoengine;

#endif