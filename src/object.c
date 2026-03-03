/**
 * ISOENGINE
 * object.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "object.h"
#include "macro.h"
#include "engine.h"
#include "memory.h"

#include <stdlib.h>

bool _object_handle_keys(isoengine *engine, const bool *const scancodes) {
    isoengine *eng = (isoengine *)engine;
    
    if(!eng) {
        ERROR("nullptr");
        return false;
    }
    
    // Handle 3d objects
    {
        uint32_t object3d_count = eng->object3d_count;
        isoengine_object3d *objects3d = eng->objects3d;

        for(int i = 0; i < object3d_count; i++) {
            isoengine_object3d *object3d = objects3d + i;
            isoengine_object3d_keypress_callback_func callback = object3d->keypress_callback;
            if(callback) {
                for(int key = 0; key < ISO_SCANCODE_COUNT; key++) {
                    if(scancodes[key]) {
                        object3d->coords = callback(&object3d->coords, key);
                    }
                }
            }
        }
    }

    // Handle 2d objects
    {
        uint32_t object2d_count = eng->object2d_count;
        isoengine_object2d *objects2d = eng->objects2d;

        for(int i = 0; i < object2d_count; i++) {
            isoengine_object2d *object2d = objects2d + i;
            isoengine_object2d_keypress_callback_func callback = object2d->keypress_callback;
            if(callback) {
                for(int key = 0; key < ISO_SCANCODE_COUNT; key++) {
                    if(scancodes[key]) {
                        object2d->coords = callback(&object2d->coords, key);
                    }
                }
            }
        }
    }

    return true;
}

void *isoengine_object3d_create(void *engine, const isoengine_3dcoords * const coords) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return nullptr;
    }

    // Grow the object buffer in chunks of 1024 if capacity is exceeded.
    // Uses a temporary pointer so the original buffer is preserved on failure.
    eng->object3d_count++;
    if(eng->object3d_count > eng->object3d_buffer_len) {
        size_t old_nmemb = eng->object3d_buffer_len;
        eng->object3d_buffer_len += 1024;
        
        isoengine_object3d *objects3d = (isoengine_object3d *)recalloc(eng->objects3d, old_nmemb, eng->object3d_buffer_len, sizeof(isoengine_object3d));
        if(objects3d == nullptr) {
            ERROR("Out of memory");
            eng->object3d_buffer_len -= 1024;
            eng->object3d_count--;
            return nullptr;
        }

        eng->objects3d = objects3d;
    }

    isoengine_object3d *obj = eng->objects3d + (eng->object3d_count - 1);

    obj->coords = *coords;

    return obj;
}

void *isoengine_object2d_create(void *engine, const isoengine_2dcoords * const coords) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return nullptr;
    }

    // Grow the object buffer in chunks of 1024 if capacity is exceeded.
    // Uses a temporary pointer so the original buffer is preserved on failure.
    eng->object2d_count++;
    if(eng->object2d_count > eng->object2d_buffer_len) {
        size_t old_nmemb = eng->object2d_buffer_len;
        eng->object2d_buffer_len += 1024;
        
        isoengine_object2d *objects2d = (isoengine_object2d *)recalloc(eng->objects2d, old_nmemb, eng->object2d_buffer_len, sizeof(isoengine_object2d));
        if(objects2d == nullptr) {
            ERROR("Out of memory");
            eng->object2d_buffer_len -= 1024;
            eng->object2d_count--;
            return nullptr;
        }

        eng->objects2d = objects2d;
    }

    isoengine_object2d *obj = eng->objects2d + (eng->object2d_count - 1);

    obj->coords = *coords;

    return obj;
}

bool isoengine_object2d_texture(void *engine, void *object2d, const char *filepng) {
    isoengine *eng = (isoengine *)engine;
    isoengine_object2d *obj = (isoengine_object2d *)object2d;
    
    if(obj == nullptr || eng == nullptr || eng->renderer == nullptr) {
        ERROR("Stop with da nullptr yo");
        return false;
    }

    SDL_Surface *tex_surface = SDL_LoadPNG(filepng);
    if(tex_surface == nullptr) {
        ERROR("Failed to load png: %s", SDL_GetError());
        return false;
    }

    obj->texture = SDL_CreateTextureFromSurface(eng->renderer, tex_surface);
    if(obj->texture == nullptr) {
        ERROR("Failed to convert surface to texture: %s", SDL_GetError());
        SDL_DestroySurface(tex_surface);
        return false;
    }

    SDL_DestroySurface(tex_surface);

    return true;
}

bool isoengine_object3d_keypress_callback(void *object3d, isoengine_object3d_keypress_callback_func callback) {
    isoengine_object3d *obj = (isoengine_object3d *)object3d;
    
    if(obj == nullptr) {
        ERROR("Object3d cannot be nullptr");
        return false;
    }

    obj->keypress_callback = callback;

    return true;
}

bool isoengine_object2d_keypress_callback(void *object2d, isoengine_object2d_keypress_callback_func callback) {
    isoengine_object2d *obj = (isoengine_object2d *)object2d;
    
    if(obj == nullptr) {
        ERROR("Object2d cannot be nullptr");
        return false;
    }

    obj->keypress_callback = callback;

    return true;
}