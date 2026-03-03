/**
 * ISOENGINE
 * clock.c
 * 
 * matt.g@castus.tv
 */

#include "clock.h"
#include "macro.h"

#include <stdio.h>
#include <time.h>

bool _start_clock(isoengine *engine) {
    if(!engine) {
        ERROR("bad nullptr :(");
        return false;
    }

    clock_gettime(CLOCK_MONOTONIC, &engine->prev);

    return true;
}

bool _cycle_clock(isoengine *engine, double *res) {
    if(!engine || !res) {
        ERROR("bad nullptr :(");
        return false;
    }
    
    struct timespec cur;
    clock_gettime(CLOCK_MONOTONIC, &cur);
    *res = (double)(cur.tv_sec - engine->prev.tv_sec)
         + (double)(cur.tv_nsec - engine->prev.tv_nsec) / 1e9;
    engine->prev = cur;
    return true;
}