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
        uint32_t object2d_blen = engine->object2d_buffer_len;
        isoengine_object2d *objects2d = engine->objects2d;

        for(uint32_t j = 0; j < object2d_blen; j++) {
            isoengine_object2d *object2d = objects2d + j;
            if(object2d->id) {
                isoengine_object2d_keypress_callback_func callback = object2d->keypress_callback;
                if(callback) {
                    object2d->coords = callback(&object2d->coords, scancodes, dt);
                }
            }
        }
    }

    return true;
}

/**
 * Pop a free slot index from the free stack.
 * Returns the slot index, or UINT32_MAX if no free slots.
 */
static uint32_t _object2d_alloc_slot(isoengine *engine) {
    if(!engine || !engine->free_stack) {
        return UINT32_MAX;
    }
    if(engine->free_stack_top == 0) {
        return UINT32_MAX;
    }
    engine->free_stack_top--;
    return engine->free_stack[engine->free_stack_top];
}

/**
 * Push a slot index back onto the free stack.
 */
static void _object2d_free_slot(isoengine *engine, uint32_t index) {
    if(!engine || !engine->free_stack) {
        return;
    }
    engine->free_stack[engine->free_stack_top] = index;
    engine->free_stack_top++;
}

static inline isoengine_object2d *_object2d_find_by_id(isoengine *engine, uint32_t objectid) {
    if(!engine || !engine->objects2d || objectid == 0 || objectid > engine->object2d_buffer_len) {
        return nullptr;
    }

    isoengine_object2d *obj = &engine->objects2d[objectid - 1];
    if(obj->id != objectid) {
        return nullptr;
    }
    
    return obj;
}

bool isoengine_object2d_delete(void *engine, uint32_t objectid) {
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

    uint32_t index = objectid - 1;
    memset(obj, 0, sizeof(isoengine_object2d));
    eng->object2d_count--;
    _object2d_free_slot(eng, index);

    return true;
}

uint32_t isoengine_object2d_create(void *engine, const isoengine_2dcoords * const coords) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return 0;
    }

    // Try to get a free slot from the stack
    uint32_t index = _object2d_alloc_slot(eng);

    // If no free slots, grow the buffer
    if(index == UINT32_MAX) {
        size_t old_len = eng->object2d_buffer_len;
        size_t new_len = old_len + OBJECT_BUFFER_SIZE;

        DEBUG("Growing 2d object buffer %ld --> %ld", old_len * sizeof(isoengine_object2d), new_len * sizeof(isoengine_object2d));

        isoengine_object2d *objects2d = (isoengine_object2d *)recalloc(eng->objects2d, old_len, new_len, sizeof(isoengine_object2d));
        if(objects2d == nullptr) {
            ERROR("Out of memory");
            return 0;
        }
        eng->objects2d = objects2d;

        // Grow the free stack
        uint32_t *new_stack = (uint32_t *)realloc(eng->free_stack, new_len * sizeof(uint32_t));
        if(new_stack == nullptr) {
            ERROR("Out of memory");
            return 0;
        }
        eng->free_stack = new_stack;

        // Push new slots onto the free stack (in reverse so lowest indices are popped first)
        for(size_t i = new_len - 1; i >= old_len + 1; i--) {
            eng->free_stack[eng->free_stack_top] = (uint32_t)i;
            eng->free_stack_top++;
        }

        eng->object2d_buffer_len = (uint32_t)new_len;

        // Use old_len as the slot for this object (lowest new index)
        index = (uint32_t)old_len;
    }

    uint32_t id = index + 1;
    isoengine_object2d *obj = &eng->objects2d[index];
    obj->coords = *coords;
    obj->id = id;
    eng->object2d_count++;

    return id;
}

bool isoengine_object2d_texture(void *engine, uint32_t objectid, const char *filepng) {
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

bool isoengine_object2d_keypress_callback(void *engine, uint32_t objectid, isoengine_object2d_keypress_callback_func callback) {
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