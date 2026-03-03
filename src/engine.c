/**
 * ISOENGINE
 * engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"
#include "macro.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL.h>

void *isoengine_create() {
    void *engine = calloc(1, sizeof(isoengine));
    if(engine == nullptr) {
        ERROR("Out of Memory");
        return nullptr;
    }

    isoengine *eng = (isoengine *)engine;

    eng->object3d_buffer_len = 1024;
    eng->objects3d = calloc(eng->object3d_buffer_len, sizeof(isoengine_object3d));
    if(eng->objects3d == nullptr) {
        ERROR("Out of memory");
        free(engine);
        return nullptr;
    }

    eng->object2d_buffer_len = 1024;
    eng->objects2d = calloc(eng->object2d_buffer_len, sizeof(isoengine_object2d));
    if(eng->objects2d == nullptr) {
        ERROR("Out of memory");
        free(eng->objects3d);
        free(eng);
        return nullptr;
    }

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        ERROR("SDL_Init failed: %s", SDL_GetError());
        free(engine);
        return nullptr;
    }

    return engine;
}

bool isoengine_destroy(void *engine) {
    isoengine *eng = (isoengine *)engine;
    
    if(eng == nullptr) {
        ERROR("Stop giving me null pointers...");
        return false;
    }

    if(eng->renderer) {
        SDL_DestroyRenderer(eng->renderer);
        eng->renderer = nullptr;
    }

    if(eng->window) {
        SDL_DestroyWindow(eng->window);
        eng->window = nullptr;
    }

    if(eng->objects3d) {
        for(size_t i = 0; i < eng->object3d_count; i++) {
            if(eng->objects3d[i].texture) {
                SDL_DestroyTexture(eng->objects3d[i].texture);
                eng->objects3d[i].texture = nullptr;
            }
        }

        free(eng->objects3d);
        eng->objects3d = nullptr;
    }

    if(eng->objects2d) {
        for(size_t i = 0; i < eng->object2d_count; i++) {
            if(eng->objects2d[i].texture) {
                SDL_DestroyTexture(eng->objects2d[i].texture);
                eng->objects2d[i].texture = nullptr;
            }
        }
        
        free(eng->objects2d);
        eng->objects2d = nullptr;
    }

    free(eng);

    SDL_Quit();

    return true;
}

bool isoengine_handle_events(void *engine) {
    static uint32_t keycount = 0;
    static bool scancodes[ISO_SCANCODE_COUNT] = {};
    SDL_Event event = {};
    isoengine *eng = (isoengine *)engine;

    if(eng == nullptr) {
        ERROR("Stop giving me null pointers...");
        return false;
    }

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                return false;
            case SDL_EVENT_KEY_DOWN:
                scancodes[event.key.scancode] = true;
                keycount++;
                break;
            case SDL_EVENT_KEY_UP:
                scancodes[event.key.scancode] = false;
                keycount--;
                break;
        }
    }

    if(keycount) {
        if(!_object_handle_keys(eng, scancodes)) {
            ERROR("Object handle keys");
            return false;
        }
    }

    return true;
}