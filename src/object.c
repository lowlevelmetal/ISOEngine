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

    uint32_t object_count = eng->object_count;
    isoengine_object *objects = eng->objects;

    for(int i = 0; i < object_count; i++) {
        isoengine_object *object = objects + i;
        isoengine_keypress_callback callback = object->keypress_callback;
        if(callback) {
            for(int key = 0; key < ISO_SCANCODE_COUNT; key++) {
                if(scancodes[key]) {
                    object->coords = callback(&object->coords, key);
                }
            }
        }
    }

    return true;
}

void *isoengine_object_create(void *engine, const isoengine_3dcoords * const coords) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return nullptr;
    }

    // Grow the object buffer in chunks of 1024 if capacity is exceeded.
    // Uses a temporary pointer so the original buffer is preserved on failure.
    eng->object_count++;
    if(eng->object_count > eng->object_buffer_len) {
        size_t old_nmemb = eng->object_buffer_len;
        eng->object_buffer_len += 1024;
        
        isoengine_object *objects = (isoengine_object *)recalloc(eng->objects, old_nmemb, eng->object_buffer_len, sizeof(isoengine_object));
        if(objects == nullptr) {
            ERROR("Out of memory");
            eng->object_buffer_len -= 1024;
            eng->object_count--;
            return nullptr;
        }

        eng->objects = objects;
    }

    isoengine_object *obj = eng->objects + (eng->object_count - 1);

    obj->coords = *coords;

    return obj;
}

bool isoengine_object_keypress_callback(void *object, isoengine_keypress_callback callback) {
    isoengine_object *obj = (isoengine_object *)object;
    
    if(obj == nullptr) {
        ERROR("Object cannot be nullptr");
    }

    obj->keypress_callback = callback;
}