/**
 * ISOENGINE
 * engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"
#include "engine.h"
#include "macro.h"

void *isoengine_create() {
    void *engine = calloc(1, sizeof(isoengine));
    if(engine == nullptr) {
        ERROR("Out of Memory");
    }

    return engine;
}