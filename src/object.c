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
    if(!engine) {
        ERROR("nullptr");
        return false;
    }

    // Handle 2d objects
    {
        uint32_t object2d_blen = engine->object2d_buffer_len;
        isoengine_object2d *objects2d = engine->objects2d;

        for(uint32_t j = 0; j < object2d_blen; j++) {
            isoengine_object2d *object2d = objects2d + j;
            isoengine_object2d_keypress_callback_func callback = object2d->keypress_callback;
            uint32_t id = object2d->id;
            if(id && callback) {
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

static uint32_t _object2d_find_available_id(isoengine *engine) {
    if(!engine) {
        ERROR("Fuck off nullptr!");
        return 0;
    }

    isoengine_object2d *objects = engine->objects2d;
    uint32_t object_blen = engine->object2d_buffer_len;

    for(uint32_t j = 0; j < object_blen; j++) {
        if(!objects[j].id) {
            objects[j].id = j + 1;
            return j + 1;
        }
    }

    return 0;
}

uint32_t isoengine_object2d_create(void *engine, const isoengine_2dcoords * const coords) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return 0;
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
            return 0;
        }

        eng->objects2d = objects2d;
    }

    uint32_t object_id = _object2d_find_available_id(eng);
    if(!object_id) {
        ERROR("Failed to find available object id");
        eng->object2d_count--;
        return 0;
    }

    isoengine_object2d *obj = eng->objects2d + (object_id-1);
    obj->coords = *coords;

    return object_id;
}

bool isoengine_object2d_texture(void *engine, uint32_t objectid, const char *filepng) {
    isoengine *eng = (isoengine *)engine;
    
    if(!eng || !eng->objects2d || !eng->renderer) {
        ERROR("Stop with da nullptr yo");
        return false;
    }

    if(objectid == 0 || objectid > eng->object2d_buffer_len) {
        ERROR("Object id out of range");
        return false;
    }

    isoengine_object2d *obj = eng->objects2d + (objectid-1);
    if(obj->id != objectid) {
        ERROR("Object id mismatch");
        return false;
    }

    if(obj->texture) {
        SDL_DestroyTexture(obj->texture);
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

bool isoengine_object2d_keypress_callback(void *engine, uint32_t objectid, isoengine_object2d_keypress_callback_func callback) {
    isoengine *eng = (isoengine *)engine;
    if(!eng) {
        ERROR("No nullptr :()");
        return false;
    }

    if(objectid == 0 || objectid > eng->object2d_buffer_len) {
        ERROR("Object id out of range");
        return false;
    }

    isoengine_object2d *obj = eng->objects2d + (objectid-1);
    if(obj->id != objectid) {
        ERROR("Object id mismatch");
        return false;
    }

    obj->keypress_callback = callback;

    return true;
}