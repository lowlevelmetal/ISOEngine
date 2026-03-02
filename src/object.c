/**
 * ISOENGINE
 * object.c
 * 
 * matt.g@castus.tv
 */

#include "object.h"
#include "macro.h"
#include "engine.h"
#include "memory.h"

#include <stdlib.h>

void *isoengine_object_create(void *engine, uint32_t posx, uint32_t posy) {
    isoengine *eng = (isoengine *)engine;
    if(eng == nullptr) {
        ERROR("No nullptrs!");
        return nullptr;
    }

    // Grow the object buffer in chunks of 1024 if capacity is exceeded.
    // Uses a temporary pointer so the original buffer is preserved on failure.
    eng->object_count++;
    if(eng->object_count > eng->object_buffer_len) {
        eng->object_buffer_len += 1024;
        
        isoengine_object *objects = (isoengine_object *)recalloc(eng->objects, eng->object_buffer_len, sizeof(isoengine_object));
        if(objects == nullptr) {
            ERROR("Out of memory");
            eng->object_buffer_len -= 1024;
            eng->object_count--;
            return nullptr;
        }

        eng->objects = objects;
    }

    isoengine_object *obj = eng->objects + (eng->object_count - 1);

    obj->x = posx;
    obj->y = posy;

    return obj;
}

bool isoengine_object_keypress_callback(void *object, isoengine_keypress_callback callback) {
    isoengine_object *obj = (isoengine_object *)object;
    
    if(obj == nullptr) {
        ERROR("Object cannot be nullptr");
    }

    obj->keypress_callback = callback;
}