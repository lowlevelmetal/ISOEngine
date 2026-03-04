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
#include <stdckdint.h>

bool _object_handle_keys(isoengine *engine, const bool *const scancodes, double dt) {    
    if(!engine) {
        ERROR("nullptr");
        return false;
    }

    // Handle 2d objects
    {
        uint32_t found = 0;
        uint32_t object2d_count = engine->object2d_count;
        uint32_t object2d_blen = engine->object2d_buffer_len;
        isoengine_object2d *objects2d = engine->objects2d;

        for(uint32_t j = 0; j < object2d_blen && found < object2d_count; j++) {
            isoengine_object2d *object2d = objects2d + j;
            isoengine_object2d_keypress_callback_func callback = object2d->keypress_callback;
            uint32_t id = object2d->id;
            if(id) {
                found++;
                if(callback) {
                    object2d->coords = callback(&object2d->coords, scancodes, dt);
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

    engine->next_object2d_id++;
    if(engine->next_object2d_id == 0) {
        ERROR("Object ID counter overflow");
        return 0;
    }

    return engine->next_object2d_id;
}

static isoengine_object2d *_object2d_find_by_id(isoengine *engine, uint64_t objectid) {
    if(!engine || !engine->objects2d) {
        ERROR("nullptr");
        return nullptr;
    }

    isoengine_object2d *objects = engine->objects2d;
    uint32_t object_blen = engine->object2d_buffer_len;

    for(uint32_t j = 0; j < object_blen; j++) {
        if(objects[j].id == objectid) {
            return &objects[j];
        }
    }

    return nullptr;
}

static isoengine_object2d *_shrink_defrag_objects2d(isoengine_object2d *objects, size_t curlen, size_t newlen, uint32_t object_count) {
    DEBUG("Shrinking and Defragging 2d objects");
    
    if(!objects) {
        ERROR("nullptr");
        return nullptr;
    }
    
    if(newlen < OBJECT_BUFFER_SIZE) {
        ERROR("New length cannot be less than minimum size");
        return nullptr;
    }

    if(newlen > curlen) {
        ERROR("New length cannot be greater than current length");
        return nullptr;
    }

    if(newlen % OBJECT_BUFFER_SIZE) {
        ERROR("New length must be divisible by global buffer size");
        return nullptr;
    }

    if(object_count > newlen) {
        ERROR("Object count must be less than or equal to the new length");
        return nullptr;
    }

    isoengine_object2d *newobjects = (isoengine_object2d *)malloc(sizeof(isoengine_object2d) * newlen);
    if(!newobjects) {
        ERROR("out of memory");
        return nullptr;
    }

    {
        size_t newindex = 0;
        for(size_t i = 0; i < curlen && newindex < object_count; i++) {
            if(objects[i].id) {
                newobjects[newindex] = objects[i];
                newindex++;
            }
        }

    }
    
    return newobjects;
}

bool isoengine_object2d_delete(void *engine, uint64_t objectid) {
    isoengine *eng = (isoengine *)engine;
    
    if(!eng || !eng->objects2d) {
        ERROR("nullptr");
        return false;
    }

    if(objectid == 0) {
        ERROR("Object id cannot be zero");
        return false;
    }

    isoengine_object2d *obj = _object2d_find_by_id(eng, objectid);
    if(!obj) {
        ERROR("Object not found");
        return false;
    }

    if(obj->texture) {
        SDL_DestroyTexture(obj->texture);
    }

    memset(obj, 0, sizeof(isoengine_object2d));

    {
        eng->object2d_count--;
        size_t newbufsize = eng->object2d_buffer_len - OBJECT_BUFFER_SIZE;
        if(eng->object2d_count < newbufsize) {
            isoengine_object2d *oldobjects = eng->objects2d;
            isoengine_object2d *newobjects = _shrink_defrag_objects2d(oldobjects, eng->object2d_buffer_len, newbufsize, eng->object2d_count);
            if(!newobjects) {
                ERROR("Failed to defrag object buffer");
                return false;
            }

            free(oldobjects);
            eng->object2d_buffer_len = newbufsize;
            eng->objects2d = newobjects;
        }
    }

    return true;
}

uint64_t isoengine_object2d_create(void *engine, const isoengine_2dcoords * const coords) {
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

    uint64_t object_id = _object2d_find_available_id(eng);
    if(!object_id) {
        ERROR("Failed to find available object id");
        eng->object2d_count--;
        return 0;
    }

    // Find the first empty slot in the buffer
    isoengine_object2d *obj = nullptr;
    for(uint32_t j = 0; j < eng->object2d_buffer_len; j++) {
        if(!eng->objects2d[j].id) {
            obj = eng->objects2d + j;
            break;
        }
    }
    if(!obj) {
        ERROR("Failed to find empty slot");
        eng->object2d_count--;
        return 0;
    }

    obj->coords = *coords;
    obj->id = object_id;

    return object_id;
}

bool isoengine_object2d_texture(void *engine, uint64_t objectid, const char *filepng) {
    isoengine *eng = (isoengine *)engine;
    
    if(!eng || !eng->objects2d || !eng->renderer) {
        ERROR("Stop with da nullptr yo");
        return false;
    }

    if(objectid == 0) {
        ERROR("Object id cannot be zero");
        return false;
    }

    isoengine_object2d *obj = _object2d_find_by_id(eng, objectid);
    if(!obj) {
        ERROR("Object not found");
        return false;
    }

    // If we are changing the texture, lets first delete the existing one.
    if(obj->texture) {
        SDL_DestroyTexture(obj->texture);
        obj->texture = nullptr;
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

bool isoengine_object2d_keypress_callback(void *engine, uint64_t objectid, isoengine_object2d_keypress_callback_func callback) {
    isoengine *eng = (isoengine *)engine;
    if(!eng) {
        ERROR("No nullptr :()");
        return false;
    }

    if(objectid == 0) {
        ERROR("Object id cannot be zero");
        return false;
    }

    isoengine_object2d *obj = _object2d_find_by_id(eng, objectid);
    if(!obj) {
        ERROR("Object not found");
        return false;
    }

    obj->keypress_callback = callback;

    return true;
}