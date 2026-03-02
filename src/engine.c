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

    free(eng);

    SDL_Quit();
}

bool isoengine_handle_events(void *engine) {
    SDL_Event event;
    isoengine *eng = (isoengine *)engine;

    if(eng == nullptr) {
        ERROR("Stop giving me null pointers...");
        return false;
    }

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                return false;
        }
    }

    return true;
}