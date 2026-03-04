/**
 * ISOENGINE
 * engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"
#include "macro.h"
#include "clock.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL.h>

void *isoengine_create() {
    isoengine *eng = nullptr;
    void *engine = calloc(1, sizeof(isoengine));
    if(engine == nullptr) {
        ERROR("Out of Memory");
        return nullptr;
    }

    eng = (isoengine *)engine;

    eng->object2d_buffer_len = 1024;
    eng->objects2d = calloc(eng->object2d_buffer_len, sizeof(isoengine_object2d));
    if(eng->objects2d == nullptr) {
        ERROR("Out of memory");
        goto ERROR;
    }

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        ERROR("SDL_Init failed: %s", SDL_GetError());
        goto ERROR;
    }

    if(!_start_clock(eng)) {
        ERROR("Failed to start clock");
        goto ERROR;
    }

    return engine;

ERROR:
    if(eng) {
        if(eng->objects2d) {
            free(eng->objects2d);
        }

        free(eng);
    }

    return nullptr;
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

    if(eng->objects2d) {
        uint32_t found = 0;
        for(size_t i = 0; i < eng->object2d_buffer_len && found < eng->object2d_count; i++) {
            if(!eng->objects2d[i].id) {
                continue;
            }
            found++;
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
    double dt = 0.0;
    static uint32_t keycount = 0;
    static bool scancodes[ISO_SCANCODE_COUNT] = {};
    SDL_Event event = {};
    isoengine *eng = (isoengine *)engine;

    if(eng == nullptr) {
        ERROR("Stop giving me null pointers...");
        return false;
    }

    if(!_cycle_clock(eng, &dt)) {
        ERROR("Failed to cycle clock");
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
        if(!_object_handle_keys(eng, scancodes, dt)) {
            ERROR("Object handle keys");
            return false;
        }
    }

    return true;
}