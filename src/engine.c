/**
 * ISOENGINE
 * engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/engine.h"
#include "macro.h"

isoengine *create_iso_engine() {
    isoengine *engine = (isoengine*)malloc(sizeof(isoengine));
    if(engine == NULL) {
        ERROR("Out of memory");
    }

    return engine;
}