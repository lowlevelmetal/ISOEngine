/**
 * ISOENGINE
 * object.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_OBJECT_H__
#define __ISOENGINE_OBJECT_H__

#include <SDL3/SDL_render.h>

#include "isoengine/isoengine.h"

#ifndef OBJECT_BUFFER_SIZE
#define OBJECT_BUFFER_SIZE 1024
#endif

typedef struct isoengine_object2d {
    uint32_t id;
    isoengine_object2d_keypress_callback_func keypress_callback;
    isoengine_2dcoords coords;
    SDL_Texture *texture;
} isoengine_object2d;

struct isoengine;
bool _object_handle_keys(struct isoengine *engine, const bool *const scancodes, double dt);

#endif