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

typedef struct isoengine_object3d {
    uint32_t id;
    isoengine_object3d_keypress_callback_func keypress_callback;
    isoengine_3dcoords coords;
    SDL_Texture *texture;
} isoengine_object3d;

typedef struct isoengine_object2d {
    uint32_t id;
    isoengine_object2d_keypress_callback_func keypress_callback;
    isoengine_2dcoords coords;
    SDL_Texture *texture;
} isoengine_object2d;

struct isoengine;
bool _object_handle_keys(struct isoengine *engine, const bool *const scancodes);

#endif